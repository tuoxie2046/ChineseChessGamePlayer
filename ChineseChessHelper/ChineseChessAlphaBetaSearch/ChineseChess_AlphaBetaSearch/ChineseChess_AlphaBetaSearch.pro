#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T19:10:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ChineseChess_AlphaBetaSearch
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ChineseChessAlphaBetaSearch.cpp \
    ChineseChessMover.cpp \
    ChineseChessEvaluatorPosition.cpp \
    ChineseChessEvaluatorChess.cpp

HEADERS += \
    ChineseChessAlphaBetaSearch.h \
    ChineseChessMover.h \
    ChineseChessEvaluatorPosition.h \
    ChineseChessEvaluator.h \
    ChineseChessEvaluatorChess.h
