#ifndef HEATSHRINK_DECODER_H
#define HEATSHRINK_DECODER_H

#include "heatshrink_common.h"
#include "heatshrink_config.h"

typedef enum {
    HSDR_SINK_OK,               /* data sunk, ready to poll */
    HSDR_SINK_FULL,             /* out of space in internal buffer */
    HSDR_SINK_ERROR_NULL=-1,    /* NULL argument */
} HSD_sink_res;

typedef enum {
    HSDR_POLL_EMPTY,            /* input exhausted */
    HSDR_POLL_MORE,             /* more data remaining, call again w/ fresh output buffer */
    HSDR_POLL_ERROR_NULL=-1,    /* NULL arguments */
    HSDR_POLL_ERROR_UNKNOWN=-2,
} HSD_poll_res;

typedef enum {
    HSDR_FINISH_DONE,           /* output is done */
    HSDR_FINISH_MORE,           /* more output remains */
    HSDR_FINISH_ERROR_NULL=-1,  /* NULL arguments */
} HSD_finish_res;

#if HEATSHRINK_DYNAMIC_ALLOC
#define HEATSHRINK_DECODER_INPUT_BUFFER_SIZE(BUF) \
    ((BUF)->input_buffer_size)
#define HEATSHRINK_DECODER_WINDOW_BITS(BUF) \
    ((BUF)->window_sz2)
#define HEATSHRINK_DECODER_LOOKAHEAD_BITS(BUF) \
    ((BUF)->lookahead_sz2)
#else
#define HEATSHRINK_DECODER_INPUT_BUFFER_SIZE(_) \
    HEATSHRINK_STATIC_INPUT_BUFFER_SIZE
#define HEATSHRINK_DECODER_WINDOW_BITS(_) \
    (HEATSHRINK_STATIC_WINDOW_BITS)
#define HEATSHRINK_DECODER_LOOKAHEAD_BITS(BUF) \
    (HEATSHRINK_STATIC_LOOKAHEAD_BITS)
#endif

typedef struct {
    unsigned short input_size;        /* bytes in input buffer */
    unsigned short input_index;       /* offset to next unprocessed input byte */
    unsigned short output_count;      /* how many bytes to output */
    unsigned short output_index;      /* index for bytes to output */
    unsigned short head_index;        /* head of window buffer */
    unsigned char state;              /* current state machine node */
    unsigned char current_byte;       /* current byte of input */
    unsigned char bit_index;          /* current bit index */

#if HEATSHRINK_DYNAMIC_ALLOC
    /* Fields that are only used if dynamically allocated. */
    unsigned char window_sz2;         /* window buffer bits */
    unsigned char lookahead_sz2;      /* lookahead bits */
    unsigned short input_buffer_size; /* input buffer size */

    /* Input buffer, then expansion window buffer */
    unsigned char buffers[];
#else
    /* Input buffer, then expansion window buffer */
    unsigned char buffers[(1 << HEATSHRINK_DECODER_WINDOW_BITS(_))
        + HEATSHRINK_DECODER_INPUT_BUFFER_SIZE(_)];
#endif
} heatshrink_decoder;

#if HEATSHRINK_DYNAMIC_ALLOC
/* Allocate a decoder with an input buffer of INPUT_BUFFER_SIZE bytes,
 * an expansion buffer size of 2^WINDOW_SZ2, and a lookahead
 * size of 2^lookahead_sz2. (The window buffer and lookahead sizes
 * must match the settings used when the data was compressed.)
 * Returns NULL on error. */
heatshrink_decoder *heatshrink_decoder_alloc(unsigned short input_buffer_size,
    unsigned char expansion_buffer_sz2, unsigned char lookahead_sz2);

/* Free a decoder. */
void heatshrink_decoder_free(heatshrink_decoder *hsd);
#endif

/* Reset a decoder. */
void heatshrink_decoder_reset(heatshrink_decoder *hsd);

/* Sink at most SIZE bytes from IN_BUF into the decoder. *INPUT_SIZE is set to
 * indicate how many bytes were actually sunk (in case a buffer was filled). */
HSD_sink_res heatshrink_decoder_sink(heatshrink_decoder *hsd,
    unsigned char *in_buf, unsigned long size, unsigned long *input_size);

/* Poll for output from the decoder, copying at most OUT_BUF_SIZE bytes into
 * OUT_BUF (setting *OUTPUT_SIZE to the actual amount copied). */
HSD_poll_res heatshrink_decoder_poll(heatshrink_decoder *hsd,
    unsigned char *out_buf, unsigned long out_buf_size, unsigned long *output_size);

/* Notify the dencoder that the input stream is finished.
 * If the return value is HSDR_FINISH_MORE, there is still more output, so
 * call heatshrink_decoder_poll and repeat. */
HSD_finish_res heatshrink_decoder_finish(heatshrink_decoder *hsd);

#endif
