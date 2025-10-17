QT += widgets
QT += charts
TARGET = PhotoINF
TEMPLATE = app

# CONFIGURAÇÃO DE PASTAS
SOURCES += src/main.cpp src/mainwindow.cpp
HEADERS += src/mainwindow.h
DESTDIR = bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc

# ALVO PERSONALIZADO PARA EXECUTAR O PROJETO (make run)
run.target = run
unix: run.commands = ./$$DESTDIR/$$TARGET
win32: run.commands = $$replace(DESTDIR, /, \\)\\$$TARGET.exe
run.depends = first
QMAKE_EXTRA_TARGETS += run

# Integração com OpenCV
CONFIG += link_pkgconfig
PKGCONFIG += opencv5