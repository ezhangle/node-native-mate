// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gin/per_isolate_data.h"
#include "gin/public/gin_embedders.h"
#include "uv/include/uv.h"

using v8::ArrayBuffer;
using v8::Eternal;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::FunctionTemplate;
using v8::ObjectTemplate;

namespace gin {

namespace {

uv_once_t g_once_guard;
uv_key_t g_isolate_data_key;

void InitializeThreadLocalStorage() {
  uv_key_create(&g_isolate_data_key);
}

}  // namespace

PerIsolateData::PerIsolateData(Isolate* isolate,
                               ArrayBuffer::Allocator* allocator)
    : isolate_(isolate), allocator_(allocator) {
  uv_once(&g_once_guard, InitializeThreadLocalStorage);
  uv_key_set(&g_isolate_data_key, this);
}

PerIsolateData::~PerIsolateData() {
  uv_key_set(&g_isolate_data_key, NULL);
}

PerIsolateData* PerIsolateData::From(Isolate* isolate) {
  return static_cast<PerIsolateData*>(uv_key_get(&g_isolate_data_key));
}

void PerIsolateData::SetObjectTemplate(WrapperInfo* info,
                                       Local<ObjectTemplate> templ) {
  object_templates_[info] = Eternal<ObjectTemplate>(isolate_, templ);
}

void PerIsolateData::SetFunctionTemplate(WrapperInfo* info,
                                         Local<FunctionTemplate> templ) {
  function_templates_[info] = Eternal<FunctionTemplate>(isolate_, templ);
}

v8::Local<v8::ObjectTemplate> PerIsolateData::GetObjectTemplate(
    WrapperInfo* info) {
  ObjectTemplateMap::iterator it = object_templates_.find(info);
  if (it == object_templates_.end())
    return v8::Local<v8::ObjectTemplate>();
  return it->second.Get(isolate_);
}

v8::Local<v8::FunctionTemplate> PerIsolateData::GetFunctionTemplate(
    WrapperInfo* info) {
  FunctionTemplateMap::iterator it = function_templates_.find(info);
  if (it == function_templates_.end())
    return v8::Local<v8::FunctionTemplate>();
  return it->second.Get(isolate_);
}

}  // namespace gin
