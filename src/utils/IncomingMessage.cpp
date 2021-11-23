#include <utils/IncomingMessage.h>
#include <utils/IPacketProcessor.h>
#include <utils/Pdu.h>
#include <utils/DataStream.h>
#include <utils/IPDUBank.h>
#include <iostream>

using namespace DIS;

// the DIS specification says the type is known for all PDUs at the 3rd byte of the PDU buffer.
enum
{
    PDU_TYPE_POSITION = 2,
    PDU_LENGTH_POSITION = 8,
    HEADER_SIZE = 12
};

IncomingMessage::IncomingMessage()
: _processors(), _pduBanks()
{
}

IncomingMessage::~IncomingMessage()
{
}

void IncomingMessage::Process(const char* buf, unsigned int size, Endian e)
{
   if( size < 1 )
   {
      return;
   }

   DataStream ds( buf , size , e );

   while( ds.GetReadPos() < ds.size() )
   {  
        DIS::Pdu pduHeader;
        pduHeader.unmarshal(ds);
        ds.seek(-HEADER_SIZE);
        SwitchOnType( static_cast<DIS::PDUType>(pduHeader.getPduType()), pduHeader.getLength(),  ds );
   }
}

void IncomingMessage::SwitchOnType(DIS::PDUType pdu_type, size_t pdu_length, DataStream& ds)
{
   PduSuperclass *pdu = NULL;

   PduBankContainer::iterator containerIter;

   // first, check if any custom PDU bank registered
   PduBankContainer::iterator pduBankIt = _pduBanks.find(pdu_type);
   if (pduBankIt != _pduBanks.end())
   {
      pdu = pduBankIt->second->GetStaticPDU(pdu_type, ds);
   }

   // if valid pdu point, and at least 1 processor
   if (pdu && (_processors.count(pdu_type) > 0))
   {
      pdu->unmarshal( ds );

      // assumes the location in the buffer is the packet id.
      typedef std::pair<PacketProcessorContainer::iterator,PacketProcessorContainer::iterator> RangePair;
      RangePair rangepair = _processors.equal_range( pdu_type );
      PacketProcessorContainer::iterator processor_iter = rangepair.first;
      PacketProcessorContainer::iterator processor_end = rangepair.second;
      while( processor_iter != processor_end )
      {
        (processor_iter->second)->Process( *(Pdu*)pdu );
        ++processor_iter;
      }
   }
   else
   {
       size_t offset = pdu_length;
       size_t reminder = (ds.GetReadPos() + offset) % 8;
       ds.seek(offset + reminder);
   }   
}


bool IncomingMessage::AddProcessor(unsigned char id, IPacketProcessor* pp)
{
   PacketProcessorContainer::value_type candidate(id,pp);
   PacketProcessorContainer::iterator containerIter;

   // If this id doesn't already have this processor (it shouldn't)
   if (!FindProccessorContainer(id, pp, containerIter))
   {
       _processors.insert( candidate );
       return true;
   }

   return false;    
}

///\todo add proper support for erasing from a multimap.
///\warning erases any processor registered for the id
bool IncomingMessage::RemoveProcessor(unsigned char id, const IPacketProcessor* pp)
{
   PacketProcessorContainer::iterator containerIter;

   if (FindProccessorContainer(id, pp, containerIter))
   {
      // Erases only the single pair found in the interator
      _processors.erase( containerIter );
      return true;
   }

   // The pair doesn't exist
   return false;
}

bool IncomingMessage::AddPduBank(unsigned char id, IPduBank* pduBank)
{
   PduBankContainer::value_type candidate(id,pduBank);
   PduBankContainer::iterator containerIter;

   // If this id doesn't already have this PDU bank (it shouldn't)
   if (!FindPduBankContainer(id, pduBank, containerIter))
   {
       _pduBanks.insert( candidate );
       return true;
   }

   return false;    
}

///\todo add proper support for erasing from a multimap.
///\warning erases any PDU bank registered PDU type
bool IncomingMessage::RemovePduBank(unsigned char id, const IPduBank* pduBank)
{
   PduBankContainer::iterator containerIter;

   if (FindPduBankContainer(id, pduBank, containerIter))
   {
      // Erases only the single pair found in the interator
      _pduBanks.erase( containerIter );
      return true;
   }

   // The pair doesn't exist
   return false;
}

IncomingMessage::PacketProcessorContainer& IncomingMessage::GetProcessors()
{
   return _processors;
}

const IncomingMessage::PacketProcessorContainer& IncomingMessage::GetProcessors() const
{
   return _processors;
}

IncomingMessage::PduBankContainer& IncomingMessage::GetPduBanks()
{
   return _pduBanks;
}

const IncomingMessage::PduBankContainer& IncomingMessage::GetPduBanks() const
{
   return _pduBanks;
}


bool IncomingMessage::FindProccessorContainer(unsigned char id, const IPacketProcessor* pp, PacketProcessorContainer::iterator &containerIter)
{  
   PacketProcessIteratorPair iterPair = _processors.equal_range(id);

   // Check to make sure that the processor we're trying to add is not already there
   while (iterPair.first != iterPair.second)
   {
      // If this processor with a matching id has a the exact same processor, bail
      if ((iterPair.first)->second == pp)
      {
         containerIter = iterPair.first;
         return true;
      }

      iterPair.first++;
   }

   // No matches were found in the loop
   return false;
}


bool IncomingMessage::FindPduBankContainer(unsigned char pdu_type, const IPduBank* pduBank, PduBankContainer::iterator &containerIter)
{  
   PduBankIteratorPair iterPair = _pduBanks.equal_range(pdu_type);

   // Check to make sure that the PDU bank we're trying to add is not already there
   while (iterPair.first != iterPair.second)
   {
      // If this PDU bank with a matching id has a the exact same PDU bank, bail
      if ((iterPair.first)->second == pduBank)
      {
         containerIter = iterPair.first;
         return true;
      }

      iterPair.first++;
   }

   // No matches were found in the loop
   return false;
}
