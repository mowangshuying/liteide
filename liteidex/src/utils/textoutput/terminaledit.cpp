﻿/**************************************************************************
** This file is part of LiteIDE
**
** Copyright (c) 2011-2019 LiteIDE. All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** In addition, as a special exception,  that plugins developed for LiteIDE,
** are allowed to remain closed sourced and can be distributed under any license .
** These rights are included in the file LGPL_EXCEPTION.txt in this package.
**
**************************************************************************/
// Module: terminaledit.cpp
// Creator: visualfc <visualfc@gmail.com>

#include "terminaledit.h"

#include <QTextCursor>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QMimeData>
#include <QDebug>
//lite_memory_check_begin
#if defined(WIN32) && defined(_MSC_VER) &&  defined(_DEBUG)
     #define _CRTDBG_MAP_ALLOC
     #include <stdlib.h>
     #include <crtdbg.h>
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
#endif
//lite_memory_check_end

TerminalEdit::TerminalEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    this->setCursorWidth(4);
    this->setAcceptDrops(false);
    //this->setWordWrapMode(QTextOption::NoWrap);

    m_contextMenu = new QMenu(this);
    m_contextRoMenu = new QMenu(this);

    m_bAutoPosCursor = true;
    m_bFilterTermColor = false;
    m_bTerminalInput = false;
    m_lastInputPostion = 0;
    m_lastPosition = 0;
    m_lastKey = -1;

    // 设置对象的上下文菜单策略为自定义模式
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    m_cut = new QAction(tr("Cut"),this);
    m_cut->setShortcut(QKeySequence::Cut);
    m_cut->setShortcutContext(Qt::WidgetShortcut);

    m_copy = new QAction(tr("Copy"),this);
    m_copy->setShortcut(QKeySequence::Copy);
    m_copy->setShortcutContext(Qt::WidgetShortcut);

    m_paste = new QAction(tr("Paste"),this);
    m_paste->setShortcut(QKeySequence::Paste);
    m_paste->setShortcutContext(Qt::WidgetShortcut);

    m_selectAll = new QAction(tr("Select All"),this);
    m_selectAll->setShortcut(QKeySequence::SelectAll);
    m_selectAll->setShortcutContext(Qt::WidgetShortcut);

    m_clear = new QAction(tr("Clear All"),this);

    m_contextMenu->addAction(m_cut);   // 剪切
    m_contextMenu->addAction(m_copy);  // 拷贝
    m_contextMenu->addAction(m_paste); // 粘贴
    m_contextMenu->addSeparator();     // 分割线
    m_contextMenu->addAction(m_selectAll); // 全选
    m_contextMenu->addSeparator(); // 分割线
    m_contextMenu->addAction(m_clear); // 清空

    m_contextRoMenu->addAction(m_copy);
    m_contextRoMenu->addSeparator();
    m_contextRoMenu->addAction(m_selectAll);
    m_contextRoMenu->addSeparator();
    m_contextRoMenu->addAction(m_clear);

    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuRequested(QPoint)));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(cursorPositionChanged()));
    connect(this,SIGNAL(selectionChanged()),this,SLOT(cursorPositionChanged()));
    connect(m_cut,SIGNAL(triggered()),this,SLOT(cut()));
    connect(m_copy,SIGNAL(triggered()),this,SLOT(copy()));
    connect(m_paste,SIGNAL(triggered()),this,SLOT(paste()));
    connect(m_selectAll,SIGNAL(triggered()),this,SLOT(selectAll()));
    connect(m_clear,SIGNAL(triggered()),this,SLOT(clear()));
}

void TerminalEdit::setFilterTermColor(bool filter)
{
    m_bFilterTermColor = filter;
}

void TerminalEdit::setTerminalInput(bool term)
{
    m_bTerminalInput = term;
}

void TerminalEdit::append(const QString &text, QTextCharFormat *fmt)
{
    QString str = text;
    if (m_bFilterTermColor) {
        static QRegExp rx("\033\\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]");
        str.remove(rx);
    }
    if (str.isEmpty()) {
        return;
    }
    setUndoRedoEnabled(false);
    QTextCursor cur = this->textCursor();
    cur.movePosition(QTextCursor::End);

    if (m_bTerminalInput && m_lastKey != -1) {
        cur.setPosition(m_lastInputPostion,QTextCursor::KeepAnchor);
    }
    if (fmt) {
        cur.setCharFormat(*fmt);
    }
    cur.insertText(str);
    this->setTextCursor(cur);
    setUndoRedoEnabled(true);
    m_lastPosition = this->textCursor().position();
    if (str.contains("\n") || m_lastKey == -1) {
        m_lastInputPostion = m_lastPosition;
    }
    m_lastKey = -1;
}

void TerminalEdit::clear()
{
    m_lastPosition = 0;
    m_lastInputPostion = 0;
    m_lastKey = -1;
    QPlainTextEdit::clear();
}

void TerminalEdit::keyPressEvent(QKeyEvent *ke)
{
    QTextCursor cur = this->textCursor();
    int pos = cur.position();
    int end = cur.position();

    if (cur.hasSelection()) {
        pos = cur.selectionStart();
        end = cur.selectionEnd();
    }

    bool bReadOnly = pos < m_lastInputPostion;

    if (bReadOnly && ( ke == QKeySequence::Paste || ke == QKeySequence::Cut ||
                       ke == QKeySequence::DeleteEndOfWord ||
                       ke == QKeySequence::DeleteStartOfWord)) {
        return;
    }

    if (ke == QKeySequence::DeleteStartOfWord) {
        if (!cur.hasSelection()) {
            cur.movePosition(QTextCursor::PreviousWord, QTextCursor::KeepAnchor);
            if (cur.selectionStart() < m_lastPosition) {
                cur.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,m_lastPosition-cur.selectionStart());
            }
        }
        cur.removeSelectedText();
        return;
    }
    m_lastKey = ke->key();
    if (ke->modifiers() == Qt::NoModifier
            || ke->modifiers() == Qt::ShiftModifier
            || ke->modifiers() == Qt::KeypadModifier) {
        if (ke->key() < Qt::Key_Escape) {
            if (bReadOnly) {
                return;
            }
        } else {
            if (ke->key() == Qt::Key_Backspace) {
                if (cur.hasSelection()) {
                    if (bReadOnly) {
                        return;
                    }
                } else if (pos <= m_lastInputPostion) {
                    return;
                }
            } else if (bReadOnly && (
                           ke->key() == Qt::Key_Delete ||
                           ke->key() == Qt::Key_Tab ||
                           ke->key() == Qt::Key_Backtab ||
                           ke->key() == Qt::Key_Return ||
                           ke->key() == Qt::Key_Enter)) {
                return;
            }
            if (ke->key() == Qt::Key_Return ||
                    ke->key() == Qt::Key_Enter) {
                cur.setPosition(end,QTextCursor::MoveAnchor);
                cur.setPosition(m_lastPosition,QTextCursor::KeepAnchor);
#ifdef Q_OS_WIN
                emit enterText(cur.selectedText()+"\r\n");
#else
                emit enterText(cur.selectedText()+"\n");
#endif
                QPlainTextEdit::keyPressEvent(ke);
                QTextCursor cur = this->textCursor();
                cur.movePosition(QTextCursor::End);
                return;
            } else if (ke->key() == Qt::Key_Tab){
                cur.setPosition(end,QTextCursor::MoveAnchor);
                cur.setPosition(m_lastPosition,QTextCursor::KeepAnchor);
                emit tabText(cur.selectedText()+"\t");
                return;
            } else if (ke->key() == Qt::Key_Up || ke->key() == Qt::Key_Down) {
                emit keyUpdown(ke->key());
                return;
            }
        }
    }
    QPlainTextEdit::keyPressEvent(ke);
}

void TerminalEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    QPlainTextEdit::mouseDoubleClickEvent(e);
    QTextCursor cur = cursorForPosition(e->pos());
    emit dbclickEvent(cur);
}

void TerminalEdit::mousePressEvent(QMouseEvent *e)
{
    QPlainTextEdit::mousePressEvent(e);
    if (!m_bAutoPosCursor) {
        return;
    }
    if (!this->isReadOnly() && m_bFocusOut) {
        m_bFocusOut = false;
        QTextCursor cur = this->textCursor();
        if (!cur.hasSelection()) {
            cur.movePosition(QTextCursor::End);
            this->setTextCursor(cur);
        }
    }
}

void TerminalEdit::focusOutEvent(QFocusEvent *e)
{
    QPlainTextEdit::focusOutEvent(e);
    m_bFocusOut = true;
}

void TerminalEdit::focusInEvent(QFocusEvent *e)
{
    QPlainTextEdit::focusInEvent(e);
    if (!this->isReadOnly()) {
        QTextCursor cur = this->textCursor();
        if (!cur.hasSelection()) {
            cur.movePosition(QTextCursor::End);
            this->setTextCursor(cur);
        }
    }
}

void TerminalEdit::contextMenuRequested(const QPoint &pt)
{
    QPoint globalPos = this->mapToGlobal(pt);
    if (isReadOnly()) {
        m_contextRoMenu->popup(globalPos);
    } else {
        m_contextMenu->popup(globalPos);
    }
}

void TerminalEdit::cursorPositionChanged()
{
    QTextCursor cur = this->textCursor();
    int pos = cur.position();
    if (cur.hasSelection()) {
        pos = cur.selectionStart();
        m_copy->setEnabled(true);
        if (pos < m_lastPosition) {
            m_cut->setEnabled(false);
        } else {
            m_cut->setEnabled(!this->isReadOnly());
        }
    } else {
        m_copy->setEnabled(false);
        m_cut->setEnabled(false);
    }
    if (pos < m_lastPosition) {
        m_paste->setEnabled(false);
    } else {
        QClipboard *clipboard = QApplication::clipboard();
        if (clipboard->mimeData()->hasText() ||
                clipboard->mimeData()->hasHtml()){
            m_paste->setEnabled(true);
        } else {
            m_paste->setEnabled(false);
        }
    }
}
