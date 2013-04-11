# Без этой строчки ничего не будет работать (:
APP_STL:=stlport_static
# Список модулей/либ, которые нужна забилдить. Они будут такие же как в LOCAL_MODULE в Android.mk файле
APP_MODULES      := AndroidNDK
# Указываем под какой arm собирать. Не обязательный параметр.
APP_ABI := armeabi armeabi-v7a
# Платформа, под которую билдим. Не обязательный параметр.
APP_PLATFORM := android-10