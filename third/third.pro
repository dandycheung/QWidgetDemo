TEMPLATE = subdirs
SUBDIRS += hotkey
SUBDIRS += shortcut
SUBDIRS += qwtdemo
SUBDIRS += qcustomplotdemo

#这个项目依赖QtDesigner模块,一般在arm上默认没有这个模块需要自行编译
#所以arm上如果没有QtDesigner模块不要加载下面这个子项目

lessThan(QT_MAJOR_VERSION, 5) {
SUBDIRS += designer
SUBDIRS -= hotkey
}

#Qt6有些项目还不支持
greaterThan(QT_MAJOR_VERSION, 5) {
SUBDIRS -= shortcut
SUBDIRS -= qwtdemo
#qcustomplot在qt6中暂时不支持debug套件
#准确的说是不支持6.4及以上/等官方解决以后再去掉这个限制
CONFIG(debug, debug|release) {
SUBDIRS -= qcustomplotdemo
}}

win32 {
SUBDIRS += miniblink
}
