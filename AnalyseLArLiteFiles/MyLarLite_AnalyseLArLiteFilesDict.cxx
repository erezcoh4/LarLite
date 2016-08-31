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
         instance("larlite::AnalyseEvents", "AnalyseEvents.h", 30,
                  typeid(::larlite::AnalyseEvents), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &larlitecLcLAnalyseEvents_Dictionary, isa_proxy, 4,
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
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::larlite::AnalyseEvents : new ::larlite::AnalyseEvents;
   }
   static void *newArray_larlitecLcLAnalyseEvents(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::larlite::AnalyseEvents[nElements] : new ::larlite::AnalyseEvents[nElements];
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

namespace ROOT {
   static TClass *vectorlEvectorlEboxgRsPgR_Dictionary();
   static void vectorlEvectorlEboxgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEboxgRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEboxgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEboxgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEboxgRsPgR(void *p);
   static void destruct_vectorlEvectorlEboxgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<box> >*)
   {
      vector<vector<box> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<box> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<box> >", -2, "vector", 477,
                  typeid(vector<vector<box> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEboxgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<box> >) );
      instance.SetNew(&new_vectorlEvectorlEboxgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEboxgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEboxgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEboxgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEboxgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<box> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<box> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEboxgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<box> >*)0x0)->GetClass();
      vectorlEvectorlEboxgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEboxgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEboxgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<box> > : new vector<vector<box> >;
   }
   static void *newArray_vectorlEvectorlEboxgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<box> >[nElements] : new vector<vector<box> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEboxgRsPgR(void *p) {
      delete ((vector<vector<box> >*)p);
   }
   static void deleteArray_vectorlEvectorlEboxgRsPgR(void *p) {
      delete [] ((vector<vector<box> >*)p);
   }
   static void destruct_vectorlEvectorlEboxgRsPgR(void *p) {
      typedef vector<vector<box> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<box> >

namespace ROOT {
   static TClass *vectorlEboxgR_Dictionary();
   static void vectorlEboxgR_TClassManip(TClass*);
   static void *new_vectorlEboxgR(void *p = 0);
   static void *newArray_vectorlEboxgR(Long_t size, void *p);
   static void delete_vectorlEboxgR(void *p);
   static void deleteArray_vectorlEboxgR(void *p);
   static void destruct_vectorlEboxgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<box>*)
   {
      vector<box> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<box>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<box>", -2, "vector", 477,
                  typeid(vector<box>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEboxgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<box>) );
      instance.SetNew(&new_vectorlEboxgR);
      instance.SetNewArray(&newArray_vectorlEboxgR);
      instance.SetDelete(&delete_vectorlEboxgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboxgR);
      instance.SetDestructor(&destruct_vectorlEboxgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<box> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<box>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEboxgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<box>*)0x0)->GetClass();
      vectorlEboxgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEboxgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboxgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<box> : new vector<box>;
   }
   static void *newArray_vectorlEboxgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<box>[nElements] : new vector<box>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboxgR(void *p) {
      delete ((vector<box>*)p);
   }
   static void deleteArray_vectorlEboxgR(void *p) {
      delete [] ((vector<box>*)p);
   }
   static void destruct_vectorlEboxgR(void *p) {
      typedef vector<box> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<box>

namespace ROOT {
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 477,
                  typeid(vector<TString>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace ROOT {
   static TClass *maplEintcOvectorlEvectorlEboxgRsPgRsPgR_Dictionary();
   static void maplEintcOvectorlEvectorlEboxgRsPgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p = 0);
   static void *newArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p);
   static void deleteArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p);
   static void destruct_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,vector<vector<box> > >*)
   {
      map<int,vector<vector<box> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,vector<vector<box> > >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,vector<vector<box> > >", -2, "map", 783,
                  typeid(map<int,vector<vector<box> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOvectorlEvectorlEboxgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,vector<vector<box> > >) );
      instance.SetNew(&new_maplEintcOvectorlEvectorlEboxgRsPgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR);
      instance.SetDelete(&delete_maplEintcOvectorlEvectorlEboxgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOvectorlEvectorlEboxgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,vector<vector<box> > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,vector<vector<box> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOvectorlEvectorlEboxgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,vector<vector<box> > >*)0x0)->GetClass();
      maplEintcOvectorlEvectorlEboxgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOvectorlEvectorlEboxgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<vector<box> > > : new map<int,vector<vector<box> > >;
   }
   static void *newArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<vector<box> > >[nElements] : new map<int,vector<vector<box> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p) {
      delete ((map<int,vector<vector<box> > >*)p);
   }
   static void deleteArray_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p) {
      delete [] ((map<int,vector<vector<box> > >*)p);
   }
   static void destruct_maplEintcOvectorlEvectorlEboxgRsPgRsPgR(void *p) {
      typedef map<int,vector<vector<box> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,vector<vector<box> > >

namespace ROOT {
   static TClass *maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_Dictionary();
   static void maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p);
   static void deleteArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p);
   static void destruct_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,map<int,vector<vector<box> > > >*)
   {
      map<int,map<int,vector<vector<box> > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,map<int,vector<vector<box> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,map<int,vector<vector<box> > > >", -2, "map", 783,
                  typeid(map<int,map<int,vector<vector<box> > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,map<int,vector<vector<box> > > >) );
      instance.SetNew(&new_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,map<int,vector<vector<box> > > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,map<int,vector<vector<box> > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,map<int,vector<vector<box> > > >*)0x0)->GetClass();
      maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,map<int,vector<vector<box> > > > : new map<int,map<int,vector<vector<box> > > >;
   }
   static void *newArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,map<int,vector<vector<box> > > >[nElements] : new map<int,map<int,vector<vector<box> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p) {
      delete ((map<int,map<int,vector<vector<box> > > >*)p);
   }
   static void deleteArray_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p) {
      delete [] ((map<int,map<int,vector<vector<box> > > >*)p);
   }
   static void destruct_maplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgR(void *p) {
      typedef map<int,map<int,vector<vector<box> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,map<int,vector<vector<box> > > >

namespace ROOT {
   static TClass *maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_Dictionary();
   static void maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p = 0);
   static void *newArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p);
   static void deleteArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p);
   static void destruct_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,map<int,map<int,vector<vector<box> > > > >*)
   {
      map<int,map<int,map<int,vector<vector<box> > > > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,map<int,map<int,vector<vector<box> > > > >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,map<int,map<int,vector<vector<box> > > > >", -2, "map", 783,
                  typeid(map<int,map<int,map<int,vector<vector<box> > > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,map<int,map<int,vector<vector<box> > > > >) );
      instance.SetNew(&new_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,map<int,map<int,vector<vector<box> > > > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,map<int,map<int,vector<vector<box> > > > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,map<int,map<int,vector<vector<box> > > > >*)0x0)->GetClass();
      maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,map<int,map<int,vector<vector<box> > > > > : new map<int,map<int,map<int,vector<vector<box> > > > >;
   }
   static void *newArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,map<int,map<int,vector<vector<box> > > > >[nElements] : new map<int,map<int,map<int,vector<vector<box> > > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p) {
      delete ((map<int,map<int,map<int,vector<vector<box> > > > >*)p);
   }
   static void deleteArray_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p) {
      delete [] ((map<int,map<int,map<int,vector<vector<box> > > > >*)p);
   }
   static void destruct_maplEintcOmaplEintcOmaplEintcOvectorlEvectorlEboxgRsPgRsPgRsPgRsPgR(void *p) {
      typedef map<int,map<int,map<int,vector<vector<box> > > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,map<int,map<int,vector<vector<box> > > > >

namespace {
  void TriggerDictionaryInitialization_libMyLarLite_AnalyseLArLiteFiles_Impl() {
    static const char* headers[] = {
"AnalyseEvents.h",
0
    };
    static const char* includePaths[] = {
"/Users/erezcohen/larlite/UserDev/mySoftware",
"/Users/erezcohen/larlite/UserDev/MyLarLite/MyPackage",
"/Users/erezcohen/larlite/UserDev/AnalysisTreesInformation/AnaTreesPackage",
"/Users/erezcohen/larlite/UserDev/BasicTool/GeoAlgo",
"/Users/erezcohen/larlite/core",
"/usr/local/Cellar/root6/6.06.02/include/root",
"/Users/erezcohen/larlite/UserDev/LarLite/AnalyseLArLiteFiles/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libMyLarLite_AnalyseLArLiteFiles dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace larlite{class __attribute__((annotate("$clingAutoload$AnalyseEvents.h")))  AnalyseEvents;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libMyLarLite_AnalyseLArLiteFiles dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "AnalyseEvents.h"

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
