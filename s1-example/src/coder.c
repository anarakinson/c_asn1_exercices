
#include "coder.h"

#include <ProtocolIE-Field.h>
#include <S1AP-PDU.h>
#include <SupportedTAs-Item.h>
#include <UEContextReleaseRequest.h>

#include <stdio.h>
// #include <unistd.h>
#include <sys/types.h>


#define asn1cSeqAdd(Var, Ptr) \
    if (asn_sequence_add(Var, Ptr)  != 0) assert(0)


void UEContextReleaseRequest_coder(uint8_t **buffer, ssize_t *len) {
    
    S1AP_PDU_t pdu;
    UEContextReleaseRequest_t *out = NULL;
    UEContextReleaseRequest_IEs_t *ie = NULL;

    uint32_t eNB_ue_s1ap_id = 0x01;
    uint32_t mme_ue_s1ap_id= 0x02;

    //fill pddu with zeros
    memset(&pdu, 0, sizeof(pdu));
    // set pdu content
    pdu.present = S1AP_PDU_PR_initiatingMessage;
    pdu.choice.initiatingMessage.procedureCode = ProcedureCode_id_UEContextReleaseRequest;
    pdu.choice.initiatingMessage.criticality = Criticality_ignore;
    pdu.choice.initiatingMessage.value.present = InitiatingMessage__value_PR_UEContextReleaseRequest;
    // put in out message
    out = &pdu.choice.initiatingMessage.value.choice.UEContextReleaseRequest;

    // allocate memory for 
    ie = (UEContextReleaseRequest_IEs_t *)calloc(1, sizeof(UEContextReleaseRequest_IEs_t));
    // set ie message
    ie->id = ProtocolIE_ID_id_MME_UE_S1AP_ID;
    ie->criticality = Criticality_reject;
    ie->value.present = UEContextReleaseRequest_IEs__value_PR_MME_UE_S1AP_ID;
    ie->value.choice.MME_UE_S1AP_ID = mme_ue_s1ap_id;
    // add to output list
    asn1cSeqAdd(&out->protocolIEs.list, ie);

    // reset memory
    ie = (UEContextReleaseRequest_IEs_t *)calloc(1, sizeof(UEContextReleaseRequest_IEs_t));
    // set new ie message
    ie->id = ProtocolIE_ID_id_eNB_UE_S1AP_ID;
    ie->criticality = Criticality_reject;
    ie->value.present = UEContextReleaseRequest_IEs__value_PR_ENB_UE_S1AP_ID;
    ie->value.choice.ENB_UE_S1AP_ID = eNB_ue_s1ap_id;
    // add to output list
    asn1cSeqAdd(&out->protocolIEs.list, ie);

    // reset memory
    ie = (UEContextReleaseRequest_IEs_t *)calloc(1, sizeof(UEContextReleaseRequest_IEs_t));
    // set new ie message
    ie->id = ProtocolIE_ID_id_Cause;
    ie->criticality = Criticality_ignore;
    ie->value.present = UEContextReleaseRequest_IEs__value_PR_Cause;
    ie->value.choice.Cause.present = Cause_PR_misc;
    ie->value.choice.Cause.choice.misc = CauseMisc_unknown_PLMN;
    // add to output list
    asn1cSeqAdd(&out->protocolIEs.list, ie);

    // set temporary encoding structure for result
    asn_encode_to_new_buffer_result_t res = {NULL, {0, NULL, NULL}};
    // write new encoded data to pdu
    res = asn_encode_to_new_buffer(NULL, ATS_CANONICAL_XER, &asn_DEF_S1AP_PDU, &pdu);
    // print temporary struccture parameters
    printf("%ld\n", sizeof(res));
    printf("%ld\n", strlen(res.buffer)); 
    // clear temporary buffer 
    free(res.buffer);
    // reset pdu to zeros
    memset(&res, 0, sizeof(res));
    // write data to pdu 
    res = asn_encode_to_new_buffer(NULL, ATS_ALIGNED_CANONICAL_PER, &asn_DEF_S1AP_PDU, &pdu);

    // write buffer for transmittter
    *buffer = res.buffer;
    *len = res.result.encoded;

    // check if buffer encoded
    if (*buffer == NULL) {
        fprintf(stderr, "Error enconing s1ap pdu\n");
        exit(1);
    } else {
        fprintf(stderr, "Encoded pdu\n");
    }

    // print message inn XML format
    xer_fprint(stdout, &asn_DEF_S1AP_PDU, &pdu);

}



