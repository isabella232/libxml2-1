/*
 * Summary: XML Schemastron implementation
 * Description: interface to the XML Schematron validity checking.
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */


#ifndef __XML_SCHEMATRON_H__
#define __XML_SCHEMATRON_H__

#include <libxml/xmlversion.h>

#ifdef LIBXML_SCHEMATRON_ENABLED

#include <libxml/tree.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XML_SCHEMATRON_NS BAD_CAST "http://purl.oclc.org/dsdl/schematron"

typedef enum {
    XML_SCHEMATRON_OUT_QUIET = 1 << 0,	/* quiet no report */
    XML_SCHEMATRON_OUT_TEXT = 1 << 1,	/* build a textual report */
    XML_SCHEMATRON_OUT_XML = 1 << 2,	/* output SVRL */
    XML_SCHEMATRON_OUT_FILE = 1 << 8,	/* output to a file descriptor */
    XML_SCHEMATRON_OUT_BUFFER = 1 << 9,	/* output to a buffer */
    XML_SCHEMATRON_OUT_IO = 1 << 10	/* output to I/O mechanism */
} xmlSchematronValidOptions;

/**
 * The schemas related types are kept internal
 */
typedef struct _xmlSchematron xmlSchematron;
typedef xmlSchematron *xmlSchematronPtr;

/**
 * A schemas validation context
 */
typedef void (*xmlSchematronValidityErrorFunc) (void *ctx, const char *msg, ...);
typedef void (*xmlSchematronValidityWarningFunc) (void *ctx, const char *msg, ...);

typedef struct _xmlSchematronParserCtxt xmlSchematronParserCtxt;
typedef xmlSchematronParserCtxt *xmlSchematronParserCtxtPtr;

typedef struct _xmlSchematronValidCtxt xmlSchematronValidCtxt;
typedef xmlSchematronValidCtxt *xmlSchematronValidCtxtPtr;

/*
 * Interfaces for parsing.
 */
XMLPUBFUN xmlSchematronParserCtxtPtr XMLCALL 
	    xmlSchematronNewParserCtxt	(const char *URL);
XMLPUBFUN xmlSchematronParserCtxtPtr XMLCALL 
	    xmlSchematronNewMemParserCtxt(const char *buffer,
					 int size);
XMLPUBFUN xmlSchematronParserCtxtPtr XMLCALL
	    xmlSchematronNewDocParserCtxt(xmlDocPtr doc);
XMLPUBFUN void XMLCALL		
	    xmlSchematronFreeParserCtxt	(xmlSchematronParserCtxtPtr ctxt);
XMLPUBFUN void XMLCALL		
	    xmlSchematronSetParserErrors(xmlSchematronParserCtxtPtr ctxt,
					 xmlSchematronValidityErrorFunc err,
					 xmlSchematronValidityWarningFunc warn,
					 void *ctx);
XMLPUBFUN int XMLCALL
		xmlSchematronGetParserErrors(xmlSchematronParserCtxtPtr ctxt,
					xmlSchematronValidityErrorFunc * err,
					xmlSchematronValidityWarningFunc * warn,
					void **ctx);
XMLPUBFUN int XMLCALL
		xmlSchematronIsValid	(xmlSchematronValidCtxtPtr ctxt);

XMLPUBFUN xmlSchematronPtr XMLCALL	
	    xmlSchematronParse		(xmlSchematronParserCtxtPtr ctxt);
XMLPUBFUN void XMLCALL		
	    xmlSchematronFree		(xmlSchematronPtr schema);
#ifdef LIBXML_OUTPUT_ENABLED
XMLPUBFUN void XMLCALL		
	    xmlSchematronDump		(FILE *output,
					 xmlSchematronPtr schema);
#endif /* LIBXML_OUTPUT_ENABLED */
/*
 * Interfaces for validating
 */
XMLPUBFUN void XMLCALL		
	    xmlSchematronSetValidErrors	(xmlSchematronValidCtxtPtr ctxt,
					 xmlSchematronValidityErrorFunc err,
					 xmlSchematronValidityWarningFunc warn,
					 void *ctx);
XMLPUBFUN void XMLCALL
	    xmlSchematronSetValidStructuredErrors(xmlSchematronValidCtxtPtr ctxt,
								  xmlStructuredErrorFunc serror, void *ctx);
XMLPUBFUN int XMLCALL
	    xmlSchematronGetValidErrors	(xmlSchematronValidCtxtPtr ctxt,
					 xmlSchematronValidityErrorFunc *err,
					 xmlSchematronValidityWarningFunc *warn,
					 void **ctx);
XMLPUBFUN int XMLCALL
	    xmlSchematronSetValidOptions(xmlSchematronValidCtxtPtr ctxt,
					 int options);
XMLPUBFUN int XMLCALL
	    xmlSchematronValidCtxtGetOptions(xmlSchematronValidCtxtPtr ctxt);

XMLPUBFUN xmlSchematronValidCtxtPtr XMLCALL	
	    xmlSchematronNewValidCtxt	(xmlSchematronPtr schema,
	    				 int options);
XMLPUBFUN void XMLCALL			
	    xmlSchematronFreeValidCtxt	(xmlSchematronValidCtxtPtr ctxt);
XMLPUBFUN int XMLCALL			
	    xmlSchematronValidateDoc	(xmlSchematronValidCtxtPtr ctxt,
					 xmlDocPtr instance);
XMLPUBFUN int XMLCALL
            xmlSchematronValidateOneElement (xmlSchematronValidCtxtPtr ctxt,
			                 xmlNodePtr elem);

#ifdef __cplusplus
}
#endif

#endif /* LIBXML_SCHEMATRON_ENABLED */
#endif /* __XML_SCHEMATRON_H__ */