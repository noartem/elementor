// elementor.cpp

// generated by src/napi/bindings.mjs

#pragma once

#include "elementor.h"
#include "from_napi.h"
#include "library.h"
#include "napi.h"
#include "tl/expected.hpp"
#include "to_napi.h"

class NGLPlatform : public Napi::ObjectWrap<NGLPlatform> {
public:
  NGLPlatform(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value makeWindow(const Napi::CallbackInfo &info);
  Napi::Value run(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<GLPlatform> instance;
};

class NGLWindow : public Napi::ObjectWrap<NGLWindow> {
public:
  NGLWindow(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getTitle(const Napi::CallbackInfo &info);
  Napi::Value setTitle(const Napi::CallbackInfo &info);
  Napi::Value getMinSize(const Napi::CallbackInfo &info);
  Napi::Value setMinSize(const Napi::CallbackInfo &info);
  Napi::Value getMaxSize(const Napi::CallbackInfo &info);
  Napi::Value setMaxSize(const Napi::CallbackInfo &info);
  Napi::Value setRoot(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<GLWindow> instance;
};

class NGLClipboard : public Napi::ObjectWrap<NGLClipboard> {
public:
  NGLClipboard(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value get(const Napi::CallbackInfo &info);
  Napi::Value set(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<GLClipboard> instance;
};

class NPadding : public Napi::ObjectWrap<NPadding> {
public:
  NPadding(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value setPaddings(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Padding> instance;
};

class NBackground : public Napi::ObjectWrap<NBackground> {
public:
  NBackground(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value setColor(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Background> instance;
};

class NRounded : public Napi::ObjectWrap<NRounded> {
public:
  NRounded(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value setRadius(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Rounded> instance;
};

class NRow : public Napi::ObjectWrap<NRow> {
public:
  NRow(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value appendChild(const Napi::CallbackInfo &info);
  Napi::Value getSpacing(const Napi::CallbackInfo &info);
  Napi::Value setSpacing(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Row> instance;
};

class NFlex : public Napi::ObjectWrap<NFlex> {
public:
  NFlex(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value appendChild(const Napi::CallbackInfo &info);
  Napi::Value getSpacing(const Napi::CallbackInfo &info);
  Napi::Value setSpacing(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Flex> instance;
};

class NFlexible : public Napi::ObjectWrap<NFlexible> {
public:
  NFlexible(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value getGrow(const Napi::CallbackInfo &info);
  Napi::Value setGrow(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Flexible> instance;
};

class NWidth : public Napi::ObjectWrap<NWidth> {
public:
  NWidth(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value getWidth(const Napi::CallbackInfo &info);
  Napi::Value setWidth(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Width> instance;
};

class NHeight : public Napi::ObjectWrap<NHeight> {
public:
  NHeight(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
  Napi::Value getHeight(const Napi::CallbackInfo &info);
  Napi::Value setHeight(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Height> instance;
};

class NCenter : public Napi::ObjectWrap<NCenter> {
public:
  NCenter(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getChild(const Napi::CallbackInfo &info);
  Napi::Value setChild(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Center> instance;
};

class NText : public Napi::ObjectWrap<NText> {
public:
  NText(const Napi::CallbackInfo &info);
  static Napi::Function GetClass(Napi::Env env);
  Napi::Value getInstance(const Napi::CallbackInfo &info);
  Napi::Value getSize(const Napi::CallbackInfo &info);
  Napi::Value getText(const Napi::CallbackInfo &info);
  Napi::Value setText(const Napi::CallbackInfo &info);
  Napi::Value setFontColor(const Napi::CallbackInfo &info);
  Napi::Value getFontSize(const Napi::CallbackInfo &info);
  Napi::Value setFontSize(const Napi::CallbackInfo &info);
  Napi::Value getFontSkew(const Napi::CallbackInfo &info);
  Napi::Value setFontSkew(const Napi::CallbackInfo &info);
  Napi::Value getFontScale(const Napi::CallbackInfo &info);
  Napi::Value setFontScale(const Napi::CallbackInfo &info);
  Napi::Value getFontFamily(const Napi::CallbackInfo &info);
  Napi::Value setFontFamily(const Napi::CallbackInfo &info);
private:
  std::shared_ptr<Text> instance;
};

Napi::Object Init(Napi::Env env, Napi::Object exports);