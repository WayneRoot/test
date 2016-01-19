#ifndef _COMMON_H
#define _COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MESG_TYPE_DATA,
    MESG_TYPE_STATUS,
    MESG_TYPE_FUNCTION,
    MESG_CNT
} mesg_type_e;


typedef struct __mesg_data_t {
    union {
        struct {
            int a;
        } mesg_type_data;

        struct {
             int b;            
        } mesg_type_status;

        struct {
            int function_type;
            union {
                struct {
                    unsigned char cmd_name[128];
                    //cmd result
                }func_syscmd ;
            } func_data;
        } mesg_type_function;
    } data;
} mesg_data_t;

//mesg_data resolve.
//========================================

typedef struct mesg_header {
    int id;
    int version;  //°汾ºÅ    mesg_type_e mesg_type;
    int mesg_len;
} mesg_header_t;

typedef struct mesg_buf{
    mesg_header_t  mesg_hdr;
    mesg_data_t mesg_data;  // mesg_data is the pointer which point to the first byte of mesg_header. and the buffer include the header and payload.
} mesg_buf_t;
// transmit layer header.
//==========================

#ifdef __cplusplus
}
#endif

#endif
