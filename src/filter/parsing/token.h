#ifndef TOKEN_H
#define TOKEN_H

/*
Example rule

alert stdout 22 TCP (name:"nmap_ssh_probe"; msg:"NMap SSH Probing detected"; type:str_match; target:"SSH-2.0-Nmap-SSH2-Hostkey";)

*/

/* PUNCTUATION */ 
#define R_INFO_START              "("
#define R_INFO_END                ");"
#define V_ASSIGN                  ":"
#define V_END                     ";"
#define V_STR_VAL                 "\""

/* KEYWORDS */

/* GENERIC KEYWORDS*/
#define NKEY_MSG                  "msg"         // ----------
#define NKEY_NAME                 "name"        //            \
                                                               ------- Can have any value
#define NKEY_TARGET               "target"      //            /
#define NKEY_CONTENT              "content"     // -----------
/* type can be str_match or regex */
#define NKEY_R_TYPE               "type"        
#define NKEY_SEVERITY             "sev"
#define NKEY_ALERT                "alert" // start of rule
/* PROTOCOL SPECIFIC KEYWORDS */

/* TCP */

#define NKEY_TCP_FLAGS            "flags"
#define NKEY_TCP_SEQ              "seq"
#define NKEY_TCP_ACK              "ack"

/* ICMP */

#define NKEY_ICMP_ITYPE           "itype"
#define NKEY_ICMP_ICODE           "icode"
#define NKEY_ICMP_ISEQ            "icmp_seq"
#define NKEY_ICMP_IID             "icmp_id"

/* IP */
#define NKEY_IP_TTL               "ttl"
#define NKEY_IP_PROTO             "ipproto"

#endif /* TOKEN_H */ 