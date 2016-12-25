// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MyLarLite_AnalyseLArLiteFilesDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "AnalyseEvents.h"
#include "ExtractPhysVars.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *larlitecLcLAnalyseEvents_Dictionary();
   static void larlitecLcLAnalyseEvents_TClassManip(TClass*);
   static void *new_larlitecLcLAnalyseEvents(void *p = 0);
   static void *newArray_larlitecLcLAnalyseEvents(Long_t size, void *p);
   static void delete_larlitecLcLAnalyseEvents(void *p);
   static void deleteArray_larlitecLcLAnalyseEvents(void *p);
   static void destruct_larlitecLcLAnalyseEvents(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::larlite::AnalyseEvents*)
   {
      ::larlite::AnalyseEvents *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::larlite::AnalyseEvents));
      static ::ROOT::TGenericClassInfo 
         instance("larlite::AnalyseEvents", "AnalyseEvents.h", 32,
                  typeid(::larlite::AnalyseEvents), DefineBehavior(ptr, ptr),
                  &larlitecLcLAnalyseEvents_Dictionary, isa_proxy, 0,
                  sizeof(::larlite::AnalyseEvents) );
      instance.SetNew(&new_larlitecLcLAnalyseEvents);
      instance.SetNewArray(&newArray_larlitecLcLAnalyseEvents);
      instance.SetDelete(&delete_larlitecLcLAnalyseEvents);
      instance.SetDeleteArray(&deleteArray_larlitecLcLAnalyseEvents);
      instance.SetDestructor(&destruct_larlitecLcLAnalyseEvents);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::larlite::AnalyseEvents*)
   {
      return GenerateInitInstanceLocal((::larlite::AnalyseEvents*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::larlite::AnalyseEvents*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *larlitecLcLAnalyseEvents_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::larlite::AnalyseEvents*)0x0)->GetClass();
      larlitecLcLAnalyseEvents_TClassManip(theClass);
   return theClass;
   }

   static void larlitecLcLAnalyseEvents_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_larlitecLcLAnalyseEvents(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::AnalyseEvents : new ::larlite::AnalyseEvents;
   }
   static void *newArray_larlitecLcLAnalyseEvents(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::AnalyseEvents[nElements] : new ::larlite::AnalyseEvents[nElements];
   }
   // Wrapper around operator delete
   static void delete_larlitecLcLAnalyseEvents(void *p) {
      delete ((::larlite::AnalyseEvents*)p);
   }
   static void deleteArray_larlitecLcLAnalyseEvents(void *p) {
      delete [] ((::larlite::AnalyseEvents*)p);
   }
   static void destruct_larlitecLcLAnalyseEvents(void *p) {
      typedef ::larlite::AnalyseEvents current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::larlite::AnalyseEvents

namespace {
  void TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles_Impl() {
    static const char* headers[] = {
"AnalyseEvents.h",
"ExtractPhysVars.h",
0
    };
    static const char* includePaths[] = {
"/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage",
"/Users/erezcohen/larlite/UserDev/MyLarLite/MyPackage",
"/Users/erezcohen/larlite/UserDev/LarLite/MyPackage",
"/Users/erezcohen/larlite/UserDev/AnalysisTreesInformation/AnaTreesPackage",
"/Users/erezcohen/larlite/UserDev/BasicTool/GeoAlgo",
"/Users/erezcohen/larlite/core",
"/Users/erezcohen/root6/root-6.04.10/include",
"/Users/erezcohen/larlite/UserDev/MyLarLite/AnalyseLArLiteFiles/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace larlite{class __attribute__((annotate("$clingAutoload$AnalyseEvents.h")))  AnalyseEvents;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "AnalyseEvents.h"
#include "ExtractPhysVars.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"larlite::AnalyseEvents", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libMyLarLite_AnalyseLArLiteFiles",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles() {
  TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles_Impl();
}
