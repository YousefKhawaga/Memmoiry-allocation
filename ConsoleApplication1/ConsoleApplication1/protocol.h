#pragma once
#include <iostream>
#include <time.h>

using namespace std;

#define MAX_PKT 1024 /* determines packet size in bytes */
typedef unsigned int seq_nr; /* sequence or ack numbers */
typedef struct { unsigned char data[MAX_PKT]; } packet; /* packet definition */
typedef enum { data, ack, nak } frame_kind; /* frame kind definition */
typedef struct { /* frames are transported in this layer */
	frame_kind kind; /* what kind of frame is it? */
	seq_nr seq; /* sequence number */
	seq_nr ack; /* acknowledgement number */
	packet info; /* the network layer packet */
} frame;
#define MAX_SEQ 7
typedef enum { frame_arrival, cksum_err, timeout, network_layer_ready } event_type;

/*Macro inc is expanded in - line: increment k circularly. */
#define inc(k) if (k < MAX_SEQ) k = k + 1; else k = 0


typedef struct {
};