#pragma once

#include <utils/IPduBank.h>
#include <utils/PDUType.h>
#include <utils/msLibMacro.h>

namespace DIS
{
    /// houses instances for the set of known PDU classes to be returned
    /// when provided with the PDU type's identifier value.
    class EXPORT_MACRO PduBank : IPduBank
    {
    public:
        /// finds the PDU instance corresponding to the identifier
        /// @param pdu_type the 8-bit PDU type identifier
        /// @return NULL when the pdu_type is unknown.
        ///\todo make this parameter just 'unsigned char' since that will be easier to generate.
        virtual PduSuperclass* GetStaticPDU(unsigned char pdu_type, DataStream& ds);
    };   
}


