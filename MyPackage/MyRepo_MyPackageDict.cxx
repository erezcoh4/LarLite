// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MyRepo_MyPackageDict

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
#include "AnaPandoraNuTracks.h"
#include "MyAna.h"
#include "MyLArTools.h"
#include "sample.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *larlitecLcLMyAna_Dictionary();
   static void larlitecLcLMyAna_TClassManip(TClass*);
   static void *new_larlitecLcLMyAna(void *p = 0);
   static void *newArray_larlitecLcLMyAna(Long_t size, void *p);
   static void delete_larlitecLcLMyAna(void *p);
   static void deleteArray_larlitecLcLMyAna(void *p);
   static void destruct_larlitecLcLMyAna(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::larlite::MyAna*)
   {
      ::larlite::MyAna *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::larlite::MyAna));
      static ::ROOT::TGenericClassInfo 
         instance("larlite::MyAna", "MyAna.h", 28,
                  typeid(::larlite::MyAna), DefineBehavior(ptr, ptr),
                  &larlitecLcLMyAna_Dictionary, isa_proxy, 4,
                  sizeof(::larlite::MyAna) );
      instance.SetNew(&new_larlitecLcLMyAna);
      instance.SetNewArray(&newArray_larlitecLcLMyAna);
      instance.SetDelete(&delete_larlitecLcLMyAna);
      instance.SetDeleteArray(&deleteArray_larlitecLcLMyAna);
      instance.SetDestructor(&destruct_larlitecLcLMyAna);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::larlite::MyAna*)
   {
      return GenerateInitInstanceLocal((::larlite::MyAna*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::larlite::MyAna*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *larlitecLcLMyAna_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::larlite::MyAna*)0x0)->GetClass();
      larlitecLcLMyAna_TClassManip(theClass);
   return theClass;
   }

   static void larlitecLcLMyAna_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *larlitecLcLAnaPandoraNuTracks_Dictionary();
   static void larlitecLcLAnaPandoraNuTracks_TClassManip(TClass*);
   static void *new_larlitecLcLAnaPandoraNuTracks(void *p = 0);
   static void *newArray_larlitecLcLAnaPandoraNuTracks(Long_t size, void *p);
   static void delete_larlitecLcLAnaPandoraNuTracks(void *p);
   static void deleteArray_larlitecLcLAnaPandoraNuTracks(void *p);
   static void destruct_larlitecLcLAnaPandoraNuTracks(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::larlite::AnaPandoraNuTracks*)
   {
      ::larlite::AnaPandoraNuTracks *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::larlite::AnaPandoraNuTracks));
      static ::ROOT::TGenericClassInfo 
         instance("larlite::AnaPandoraNuTracks", "AnaPandoraNuTracks.h", 78,
                  typeid(::larlite::AnaPandoraNuTracks), DefineBehavior(ptr, ptr),
                  &larlitecLcLAnaPandoraNuTracks_Dictionary, isa_proxy, 0,
                  sizeof(::larlite::AnaPandoraNuTracks) );
      instance.SetNew(&new_larlitecLcLAnaPandoraNuTracks);
      instance.SetNewArray(&newArray_larlitecLcLAnaPandoraNuTracks);
      instance.SetDelete(&delete_larlitecLcLAnaPandoraNuTracks);
      instance.SetDeleteArray(&deleteArray_larlitecLcLAnaPandoraNuTracks);
      instance.SetDestructor(&destruct_larlitecLcLAnaPandoraNuTracks);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::larlite::AnaPandoraNuTracks*)
   {
      return GenerateInitInstanceLocal((::larlite::AnaPandoraNuTracks*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::larlite::AnaPandoraNuTracks*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *larlitecLcLAnaPandoraNuTracks_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::larlite::AnaPandoraNuTracks*)0x0)->GetClass();
      larlitecLcLAnaPandoraNuTracks_TClassManip(theClass);
   return theClass;
   }

   static void larlitecLcLAnaPandoraNuTracks_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyLArTools_Dictionary();
   static void MyLArTools_TClassManip(TClass*);
   static void *new_MyLArTools(void *p = 0);
   static void *newArray_MyLArTools(Long_t size, void *p);
   static void delete_MyLArTools(void *p);
   static void deleteArray_MyLArTools(void *p);
   static void destruct_MyLArTools(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyLArTools*)
   {
      ::MyLArTools *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyLArTools));
      static ::ROOT::TGenericClassInfo 
         instance("MyLArTools", "MyLArTools.h", 29,
                  typeid(::MyLArTools), DefineBehavior(ptr, ptr),
                  &MyLArTools_Dictionary, isa_proxy, 4,
                  sizeof(::MyLArTools) );
      instance.SetNew(&new_MyLArTools);
      instance.SetNewArray(&newArray_MyLArTools);
      instance.SetDelete(&delete_MyLArTools);
      instance.SetDeleteArray(&deleteArray_MyLArTools);
      instance.SetDestructor(&destruct_MyLArTools);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyLArTools*)
   {
      return GenerateInitInstanceLocal((::MyLArTools*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyLArTools*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyLArTools_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyLArTools*)0x0)->GetClass();
      MyLArTools_TClassManip(theClass);
   return theClass;
   }

   static void MyLArTools_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_larlitecLcLMyAna(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::MyAna : new ::larlite::MyAna;
   }
   static void *newArray_larlitecLcLMyAna(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::MyAna[nElements] : new ::larlite::MyAna[nElements];
   }
   // Wrapper around operator delete
   static void delete_larlitecLcLMyAna(void *p) {
      delete ((::larlite::MyAna*)p);
   }
   static void deleteArray_larlitecLcLMyAna(void *p) {
      delete [] ((::larlite::MyAna*)p);
   }
   static void destruct_larlitecLcLMyAna(void *p) {
      typedef ::larlite::MyAna current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::larlite::MyAna

namespace ROOT {
   // Wrappers around operator new
   static void *new_larlitecLcLAnaPandoraNuTracks(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::AnaPandoraNuTracks : new ::larlite::AnaPandoraNuTracks;
   }
   static void *newArray_larlitecLcLAnaPandoraNuTracks(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::AnaPandoraNuTracks[nElements] : new ::larlite::AnaPandoraNuTracks[nElements];
   }
   // Wrapper around operator delete
   static void delete_larlitecLcLAnaPandoraNuTracks(void *p) {
      delete ((::larlite::AnaPandoraNuTracks*)p);
   }
   static void deleteArray_larlitecLcLAnaPandoraNuTracks(void *p) {
      delete [] ((::larlite::AnaPandoraNuTracks*)p);
   }
   static void destruct_larlitecLcLAnaPandoraNuTracks(void *p) {
      typedef ::larlite::AnaPandoraNuTracks current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::larlite::AnaPandoraNuTracks

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyLArTools(void *p) {
      return  p ? new(p) ::MyLArTools : new ::MyLArTools;
   }
   static void *newArray_MyLArTools(Long_t nElements, void *p) {
      return p ? new(p) ::MyLArTools[nElements] : new ::MyLArTools[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyLArTools(void *p) {
      delete ((::MyLArTools*)p);
   }
   static void deleteArray_MyLArTools(void *p) {
      delete [] ((::MyLArTools*)p);
   }
   static void destruct_MyLArTools(void *p) {
      typedef ::MyLArTools current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyLArTools

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 457,
                  typeid(vector<float>), DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlETLorentzVectorgR_Dictionary();
   static void vectorlETLorentzVectorgR_TClassManip(TClass*);
   static void *new_vectorlETLorentzVectorgR(void *p = 0);
   static void *newArray_vectorlETLorentzVectorgR(Long_t size, void *p);
   static void delete_vectorlETLorentzVectorgR(void *p);
   static void deleteArray_vectorlETLorentzVectorgR(void *p);
   static void destruct_vectorlETLorentzVectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TLorentzVector>*)
   {
      vector<TLorentzVector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TLorentzVector>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TLorentzVector>", -2, "vector", 457,
                  typeid(vector<TLorentzVector>), DefineBehavior(ptr, ptr),
                  &vectorlETLorentzVectorgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TLorentzVector>) );
      instance.SetNew(&new_vectorlETLorentzVectorgR);
      instance.SetNewArray(&newArray_vectorlETLorentzVectorgR);
      instance.SetDelete(&delete_vectorlETLorentzVectorgR);
      instance.SetDeleteArray(&deleteArray_vectorlETLorentzVectorgR);
      instance.SetDestructor(&destruct_vectorlETLorentzVectorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TLorentzVector> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETLorentzVectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0)->GetClass();
      vectorlETLorentzVectorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETLorentzVectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETLorentzVectorgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TLorentzVector> : new vector<TLorentzVector>;
   }
   static void *newArray_vectorlETLorentzVectorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TLorentzVector>[nElements] : new vector<TLorentzVector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETLorentzVectorgR(void *p) {
      delete ((vector<TLorentzVector>*)p);
   }
   static void deleteArray_vectorlETLorentzVectorgR(void *p) {
      delete [] ((vector<TLorentzVector>*)p);
   }
   static void destruct_vectorlETLorentzVectorgR(void *p) {
      typedef vector<TLorentzVector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TLorentzVector>

namespace {
  void TriggerDictionaryInitialization_libMyRepo_MyPackage_Impl() {
    static const char* headers[] = {
"AnaPandoraNuTracks.h",
"MyAna.h",
"MyLArTools.h",
"sample.h",
0
    };
    static const char* includePaths[] = {
"/Users/erezcohen/larlite/UserDev/mySoftware",
"/Users/erezcohen/larlite/core",
"/Users/erezcohen/root6/root-6.04.10/include",
"/Users/erezcohen/larlite/UserDev/MyLarLite/MyPackage/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace larlite{class __attribute__((annotate("$clingAutoload$MyAna.h")))  MyAna;}
namespace larlite{class __attribute__((annotate("$clingAutoload$AnaPandoraNuTracks.h")))  AnaPandoraNuTracks;}
class __attribute__((annotate("$clingAutoload$AnaPandoraNuTracks.h")))  MyLArTools;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "AnaPandoraNuTracks.h"
#include "MyAna.h"
#include "MyLArTools.h"
#include "sample.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MyLArTools", payloadCode, "@",
"larlite::AnaPandoraNuTracks", payloadCode, "@",
"larlite::MyAna", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libMyRepo_MyPackage",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libMyRepo_MyPackage_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libMyRepo_MyPackage_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libMyRepo_MyPackage() {
  TriggerDictionaryInitialization_libMyRepo_MyPackage_Impl();
}
