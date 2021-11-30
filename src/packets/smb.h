#ifndef __SMB_H
#define __SMB_H

struct smb2{
  uint32_t proto_id;
  uint16_t hdr_ln;
  uint16_t credit_charge;
  uint32_t NT_STATUS;
  uint16_t command;
  uint16_t credit_granted;
  uint32_t flags;
  uint32_t chain_offset;
  uint64_t message_id;
  uint32_t process_id;
  uint32_t tree_id;
  uint64_t session_id;
  uint128_t signature;  
};

struct smb2_negotiate_res{
  uint16_t structure_sz;
  uint8_t security_mode;
  uint16_t dialect;
  uint16_t negotiate_context_count;
  uint128_t server_guid;
  uint32_t capabilities;
  uint32_t max_transaction_size;
  uint32_t max_read_size;
  uint32_t max_write_size;
  uint64_t current_time;
  uint64_t boot_time;
  uint16_t blob_offset;
  uint16_t blob_ln;
  uint64_t negotiate_context_offset;
  uint8_t security_blob[blob_ln];
  
};



#endif /* __SMB_H */