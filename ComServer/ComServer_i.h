

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for ComServerModule.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ComServer_i_h__
#define __ComServer_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IATLControl_FWD_DEFINED__
#define __IATLControl_FWD_DEFINED__
typedef interface IATLControl IATLControl;

#endif 	/* __IATLControl_FWD_DEFINED__ */


#ifndef __IATLControl_FWD_DEFINED__
#define __IATLControl_FWD_DEFINED__
typedef interface IATLControl IATLControl;

#endif 	/* __IATLControl_FWD_DEFINED__ */


#ifndef __ATLControl_FWD_DEFINED__
#define __ATLControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATLControl ATLControl;
#else
typedef struct ATLControl ATLControl;
#endif /* __cplusplus */

#endif 	/* __ATLControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IATLControl_INTERFACE_DEFINED__
#define __IATLControl_INTERFACE_DEFINED__

/* interface IATLControl */
/* [unique][uuid][object][oleautomation] */ 


EXTERN_C const IID IID_IATLControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("621b055e-d513-48cf-8a36-12b41d8fb004")
    IATLControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LongRunningTask( 
            /* [in] */ IATLControl *slave) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Callback( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IATLControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IATLControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IATLControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IATLControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *LongRunningTask )( 
            IATLControl * This,
            /* [in] */ IATLControl *slave);
        
        HRESULT ( STDMETHODCALLTYPE *Callback )( 
            IATLControl * This);
        
        END_INTERFACE
    } IATLControlVtbl;

    interface IATLControl
    {
        CONST_VTBL struct IATLControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATLControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IATLControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IATLControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IATLControl_LongRunningTask(This,slave)	\
    ( (This)->lpVtbl -> LongRunningTask(This,slave) ) 

#define IATLControl_Callback(This)	\
    ( (This)->lpVtbl -> Callback(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IATLControl_INTERFACE_DEFINED__ */



#ifndef __ComServerLib_LIBRARY_DEFINED__
#define __ComServerLib_LIBRARY_DEFINED__

/* library ComServerLib */
/* [version][uuid] */ 



EXTERN_C const IID LIBID_ComServerLib;

EXTERN_C const CLSID CLSID_ATLControl;

#ifdef __cplusplus

class DECLSPEC_UUID("3254171b-5d49-4ec9-874a-e3c065c1b801")
ATLControl;
#endif
#endif /* __ComServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


