/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <stdio.h>

#include <QPushButton>

#include "QT_button.h"

bool (*button_click_function)(QPushButton* data);
extern void doQtcallback(void);

Button::Button(const QString &text, QWidget *parent): QPushButton(parent)
{
	setText(text);
	connect(this,SIGNAL(clicked()),this,SLOT(buttonClicked()));
}
typedef void (*func_ptr)(QPushButton* data);
void Button::setID(int id)
{
	this->buttonID=id;
}

void Button::setCallBack(func_ptr func)
{
	this->callback=func;
}

bool stuff(void)
{
printf("TRUE\n");
return true;
}


void Button::buttonClicked()
{
	//void*	t;
	func_ptr array_of_fun_ptr[3];

	printf("ZZZZZZZZ\n");
	printf("%i\n",this->buttonID);
	//doQtcallback(this);
	//this->callback (QPushButton*);
	//void* (*f)();
	//t=this->callback;
	//f=&this->callback;
	//f();
	array_of_fun_ptr[0]= this->callback;
	//some_a=(*(array_of_fun_ptr[0]))(void);
	//this->callback(this);
//f = A;
//f();
array_of_fun_ptr[0]	((QPushButton*)16);

}
