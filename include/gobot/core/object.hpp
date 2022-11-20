/* Copyright(c) 2020-2022, Qiqi Wu.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * This file is created by Qiqi Wu, 22-9-24
*/

#pragma once

#include "gobot/core/types.hpp"
#include "gobot/core/marcos.hpp"
#include <rttr/rttr_enable.h>

#include <QObject>

// Do nothing for 1
#define GOBOT_CLASS_1(...)    \


#define GOBOT_CLASS_2(Class, BaseClass)                                                             \
protected:                                                                                          \
    static FORCE_INLINE auto GetNotificationCallback() -> void(Object::*)(int) {                    \
         return (void(Object::*)(int)) &Class::NotificationCallBack;                                \
    }                                                                                               \
    void NotificationImpl(int notification, bool reversed) override {                               \
        if (!reversed) { BaseClass::NotificationImpl(notification, reversed); }                     \
                                                                                                    \
	    if (Class::GetNotificationCallback() != BaseClass::GetNotificationCallback()) {             \
            Notification(notification);                                                             \
		}                                                                                           \
		if (reversed) { BaseClass::NotificationImpl(notification, reversed); }                      \
    }

// Unsupported usage.
#define GOBOT_CLASS_3(...) static_assert(false, "GOBCLASS can only have 1 or 2 parameter, but you give 3!");
#define GOBOT_CLASS_4(...) static_assert(false, "GOBCLASS can only have 1 or 2 parameter, but you give 4!");
#define GOBOT_CLASS_5(...) static_assert(false, "GOBCLASS can only have 1 or 2 parameter, but you give 5!");
#define GOBOT_CLASS_6(...) static_assert(false, "GOBCLASS can only have 1 or 2 parameter, but you give 6!");


#define GOBOT_CLASS_PARAM(x) CAT2(GOBOT_CLASS_, x)

#define GOBOT_CLASS_TO_RTTR(A, ...) RTTR_ENABLE(__VA_ARGS__)


#define GOBCLASS(...)                                             \
    GOBOT_CLASS_PARAM(PP_NARG_COUNT(__VA_ARGS__))(__VA_ARGS__)    \
    GOBOT_CLASS_TO_RTTR(__VA_ARGS__)


namespace gobot::core {


enum class PropertyHint {
    None, ///< no hint provided.
    Range, ///< hint_text = "min,max[,step][,or_greater][,or_less][,hide_slider][,radians][,degrees][,exp][,suffix:<keyword>] range.
    Flags, ///< hint_text= "flag1,flag2,etc" (as bit flags)
    File, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
    Dir, ///< a directory path must be passed
    GlobalFile, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
    GlobalDir, ///< a directory path must be passed
};

enum class PropertyUsageFlags {
    None = 0,
    Storage = 1 << 1,
    Editor = 1 << 2,
    UsageDefault = Storage | Editor,
};


struct PropertyInfo {
    String name;
    PropertyHint hint = PropertyHint::None;
    String hint_string;
    PropertyUsageFlags usage = PropertyUsageFlags::None;

    PropertyInfo& SetName(const String& _name) {
        name = _name;
        return *this;
    }

    PropertyInfo& SetHint(const PropertyHint& property_hint) {
        hint = property_hint;
        return *this;
    }

    PropertyInfo& SetHint(const String& _hint_string) {
        hint_string = _hint_string;
        return *this;
    }

    PropertyInfo& SetHint(const PropertyUsageFlags& property_usage_flags) {
        usage = property_usage_flags;
        return *this;
    }


    bool operator==(const PropertyInfo &property_info) const {
        return  (name == property_info.name) &&
                (hint == property_info.hint) &&
                (hint_string == property_info.hint_string) &&
                (usage == property_info.usage);
    }

    bool operator<(const PropertyInfo &p_info) const {
        return name < p_info.name;
    }

};


class Object : public QObject {
    GOBCLASS(Object)
public:

    Object();

    template <class T>
    static T *CastTo(Object *object) {
        return dynamic_cast<T *>(object);
    }

    template <class T>
    static const T *CastTo(const Object *object) {
        return dynamic_cast<const T *>(object);
    }

protected:

    /// Notification
    void NotificationCallBack(int notification) {}

    static FORCE_INLINE auto GetNotificationCallback() -> void(Object::*)(int)  {
        return &Object::NotificationCallBack;
    }

    virtual void NotificationImpl(int notification, bool reversed) {
    }


public:
    // Notification
    void Notification(int notification, bool reversed = false) {
        NotificationImpl(notification, reversed);
    }



};


} // end of namespace gobot::core