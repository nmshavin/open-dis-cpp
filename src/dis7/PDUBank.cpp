#include <dis7/PDUBank.h>
#include <dis7/EntityStatePdu.h>
#include <dis7/FirePdu.h>
#include <dis7/DetonationPdu.h>
#include <dis7/CollisionPdu.h>
#include <dis7/ServiceRequestPdu.h>
#include <dis7/ResupplyOfferPdu.h>
#include <dis7/ResupplyReceivedPdu.h>
#include <dis7/RepairCompletePdu.h>
#include <dis7/RepairResponsePdu.h>
#include <dis7/CreateEntityPdu.h>
#include <dis7/RemoveEntityPdu.h>
#include <dis7/StartResumePdu.h>
#include <dis7/AcknowledgePdu.h>
#include <dis7/ActionRequestPdu.h>
#include <dis7/ActionResponsePdu.h>
#include <dis7/DataQueryPdu.h>
#include <dis7/SetDataPdu.h>
#include <dis7/EventReportPdu.h>
#include <dis7/CommentPdu.h>
#include <dis7/StopFreezePdu.h>
#include <dis7/ElectromagneticEmissionsPdu.h>
#include <dis7/DesignatorPdu.h>
#include <dis7/ReceiverPdu.h>
#include <dis7/IntercomSignalPdu.h>

using namespace DIS;

PduSuperclass* PduBank::GetStaticPDU(unsigned char pdu_type, DataStream& ds)
{
   static EntityStatePdu      entityStatePdu;
   static FirePdu             firePdu;
   static DetonationPdu       detonationPdu;
   static CollisionPdu        collisionPdu;
   static ServiceRequestPdu   ServiceRequestPdu;
   static ResupplyOfferPdu    resupplyOfferPdu;
   static ResupplyReceivedPdu resupplyReceivedPdu;
   static RepairCompletePdu   repairCompletePdu;
   static RepairResponsePdu   repairResponsePdu;
   static CreateEntityPdu     createEntityPdu;
   static RemoveEntityPdu     removeEntityPdu;
   static StartResumePdu      startResumePdu;
   static AcknowledgePdu      acknowledgePdu;
   static ActionRequestPdu    actionRequestPdu;
   static ActionResponsePdu   actionResponsePdu;
   static DataQueryPdu        dataQueryPdu;
   static SetDataPdu          setDataPdu;
   static EventReportPdu      eventReportPdu;
   static CommentPdu          commentPdu;
   static StopFreezePdu       stopFreezePdu;
   static ElectromagneticEmissionsPdu    electromagneticEmissionsPdu;
   static DesignatorPdu       designatorPdu;
   static ReceiverPdu         receiverPdu;
   static IntercomSignalPdu   intercomSignalPdu;

   switch(pdu_type)
   {
      case PDU_ENTITY_STATE:      return &entityStatePdu;      break;
      case PDU_FIRE:              return &firePdu;             break; 
      case PDU_DETONATION:        return &detonationPdu;       break; 
      case PDU_COLLISION:         return &collisionPdu;        break; 
      case PDU_SERVICE_REQUEST:   return &ServiceRequestPdu;   break; 
      case PDU_RESUPPLY_OFFER:    return &resupplyOfferPdu;    break; 
      case PDU_RESUPPLY_RECEIVED: return &resupplyReceivedPdu; break; 
      case PDU_REPAIR_COMPLETE:   return &repairCompletePdu;   break; 
      case PDU_REPAIR_RESPONSE:   return &repairResponsePdu;   break; 
      case PDU_CREATE_ENTITY:     return &createEntityPdu;     break; 
      case PDU_REMOVE_ENTITY:     return &removeEntityPdu;     break; 
      case PDU_START_RESUME:      return &startResumePdu;      break; 
      case PDU_ACKNOWLEDGE:       return &acknowledgePdu;      break;
      case PDU_ACTION_REQUEST:    return &actionRequestPdu;    break; 
      case PDU_ACTION_RESPONSE:   return &actionResponsePdu;   break; 
      case PDU_DATA_QUERY:        return &dataQueryPdu;        break; 
      case PDU_SET_DATA:          return &setDataPdu;          break; 
      case PDU_EVENT_REPORT:      return &eventReportPdu;      break; 
      case PDU_COMMENT:           return &commentPdu;          break; 
      case PDU_STOP_FREEZE:       return &stopFreezePdu;       break;
      case PDU_ELECTRONIC_EMMISIONS:    return &electromagneticEmissionsPdu; break;
      case PDU_DESIGNATOR:              return &designatorPdu;          break;
      case PDU_RECEIVER:          return &receiverPdu;       break;
      case PDU_INTERCOM_SIGNAL:   return &intercomSignalPdu;       break;
      default:                                                 break;
   }
   return NULL;
}

