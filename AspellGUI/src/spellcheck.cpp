/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:20:16 GMT 2015 keithdhedger@gmail.com

 * This file (spellcheck.cpp) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.

 *	  Parts of this code from aspell-0.60.6.1 example
 *	  example-c.c
 *
 *     Copyright (C) 2000-2001 by Kevin Atkinson under the GNU LGPL
 *	  license version 2.0 or 2.1.  You should have received a copy of the
 *	  LGPL license along with this library if you did not you can find it
 *	  at http://www.gnu.org/. 
*/

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <aspell.h>

#include "config.h"
#include "globals.h"
#include "guis.h"

#ifndef _USEQT5_
	#include <gtk/gtk.h>
#else
	#include <glib.h>
	#include <QtWidgets>
	#include <QObject>
	#include "QT_button.h"
#endif

bool	cancelCheck=false;

void doCancelCheck(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	gtk_widget_destroy(spellCheckWord);
#else
	((QDialog*)spellCheckWord)->done(0);
#endif

	if(badWord!=NULL)
		g_free(badWord);
	
	spellCheckWord=NULL;
	cancelCheck=true;
}

void checkTheWord(char* word,int checkDoc)
{
	int							correct;
	AspellWordList*				suggestions;
	AspellStringEnumeration*	elements;
	const char*					suggestedword;
	int							wordcnt=0;
	char*						labeltext[512];

#ifndef _USEQT5_

	correct=aspell_speller_check(spellChecker,word,-1);
	if(!correct)
		{
			badWord=word;
			cancelCheck=false;
			if(spellCheckWord==NULL)
				buildWordCheckGtk(checkDoc);
			else
				{
					for(int j=0;j<numWords;j++)
						gtk_combo_box_text_remove((GtkComboBoxText*)wordListDropbox,0);

					sprintf((char*)&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
					gtk_label_set_text((GtkLabel*)badWordLabel,(char*)&labeltext);
					gtk_label_set_use_markup((GtkLabel*)badWordLabel,true);
				}
	
			suggestions=(AspellWordList*)aspell_speller_suggest(spellChecker,word,-1);
			elements=aspell_word_list_elements(suggestions);
			while((suggestedword=aspell_string_enumeration_next(elements))!=NULL)
				{
					gtk_combo_box_text_append_text((GtkComboBoxText*)wordListDropbox,suggestedword);
					wordcnt++;
				}
			numWords=wordcnt;

			delete_aspell_string_enumeration(elements);
			gtk_combo_box_set_active((GtkComboBox*)wordListDropbox,0);
			gtk_widget_show_all(spellCheckWord);
			gtk_dialog_run((GtkDialog *)spellCheckWord);
		}
#else
	correct=aspell_speller_check(spellChecker,word,-1);
	if(!correct)
		{
			badWord=word;
			cancelCheck=false;
			if(spellCheckWord==NULL)
				buildWordCheckQt(checkDoc);
			else
				{
					for(int j=0;j<numWords;j++)
						((QComboBox*)wordListDropbox)->removeItem(0);

					sprintf((char*)&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
					((QLabel*)badWordLabel)->setText((char*)labeltext);
				}
	
			suggestions=(AspellWordList*)aspell_speller_suggest(spellChecker,word,-1);
			elements=aspell_word_list_elements(suggestions);
			while((suggestedword=aspell_string_enumeration_next(elements))!=NULL)
				{
					((QComboBox*)wordListDropbox)->addItem(suggestedword);
					wordcnt++;
				}
			numWords=wordcnt;

			delete_aspell_string_enumeration(elements);
			((QDialog*)spellCheckWord)->exec();
		}
#endif
}

void checkWord(Widget* widget,void* data)
{
	char*		selection=NULL;
#ifndef _USEQT5_
	GtkTextIter	start;
	GtkTextIter	end;

	if(gtk_text_buffer_get_selection_bounds((GtkTextBuffer*)bufferBox,&start,&end))
		{
			selection=gtk_text_buffer_get_text((GtkTextBuffer*)bufferBox,&start,&end,false);
			if(selection==NULL)
				return;
		}
	else
		return;

	gtk_text_buffer_begin_user_action((GtkTextBuffer*)bufferBox);
	checkTheWord(selection,0);
	gtk_text_buffer_end_user_action((GtkTextBuffer*)bufferBox);

	if(spellCheckWord!=NULL)
		{
			gtk_widget_destroy(spellCheckWord);
			spellCheckWord=NULL;
		}
#else
	QString		qstr;
	QByteArray	byteArray;
	const char*	str;

	if(((QPlainTextEdit*)bufferBox)->textCursor().hasSelection()==true)
		{
			qstr=((QPlainTextEdit*)bufferBox)->textCursor().selectedText();
			QByteArray byteArray=qstr.toUtf8();
			str=(char*)byteArray.constData();
			if(str==NULL)
				return;
			else
				selection=strdup(str);
		}
	else
		return;
	checkTheWord(selection,0);
#endif
}

void doChangeWord(Widget* widget,void* data)
{
#ifndef _USEQT5_
	GtkTextIter	start;
	GtkTextIter	end;

	if((long)data==0)
		{
			if(gtk_text_buffer_get_selection_bounds((GtkTextBuffer*)bufferBox,&start,&end))
				{
					badWord=gtk_text_buffer_get_text((GtkTextBuffer*)bufferBox,&start,&end,false);
					if(badWord==NULL)
						return;
				}

			goodWord=gtk_combo_box_text_get_active_text((GtkComboBoxText*)wordListDropbox);
			gtk_text_buffer_delete((GtkTextBuffer*)bufferBox,&start,&end);
			gtk_text_buffer_insert((GtkTextBuffer*)bufferBox,&start,goodWord,-1);
			g_free(goodWord);
		}
	else
		goodWord=gtk_combo_box_text_get_active_text((GtkComboBoxText*)wordListDropbox);

	aspell_speller_store_replacement(spellChecker,badWord,-1,goodWord,-1);

	gtk_dialog_response((GtkDialog*)spellCheckWord,0);
#else
	QString	qstr;
	QByteArray byteArray;
	const char* str;
	if((long)data==0)
		{
			if(((QPlainTextEdit*)bufferBox)->textCursor().hasSelection()==true)
				{
					qstr=((QPlainTextEdit*)bufferBox)->textCursor().selectedText();
					QByteArray byteArray=qstr.toUtf8();
					str=(char*)byteArray.constData();
					if(str==NULL)
						return;
					else
						badWord=strdup(str);
				}
			qstr=((QComboBox*)wordListDropbox)->currentText();
			QByteArray byteArray=qstr.toUtf8();
			str=(char*)byteArray.constData();
			if(str!=NULL)
				goodWord=strdup(str);
			((QPlainTextEdit*)bufferBox)->textCursor().insertText(goodWord);
			qApp->processEvents();
			g_free(goodWord);
		}
	else
		{
			qstr=((QComboBox*)wordListDropbox)->currentText();
			QByteArray byteArray=qstr.toUtf8();
			str=(char*)byteArray.constData();
			if(str!=NULL)
				goodWord=strdup(str);
		}

	aspell_speller_store_replacement(spellChecker,badWord,-1,goodWord,-1);
	((QDialog*)spellCheckWord)->done(0);
#endif
	if(badWord!=NULL)
		g_free(badWord);
}

void doAddIgnoreWord(Widget* widget,gpointer data)
{
#ifndef _USEQT5_
	if((long)data==1)
		aspell_speller_add_to_session(spellChecker,badWord,-1);
	else
		{
			aspell_speller_add_to_personal(spellChecker,badWord,-1);
			aspell_speller_save_all_word_lists(spellChecker);
		}

	gtk_dialog_response((GtkDialog*)spellCheckWord,0);

	if(badWord!=NULL)
		g_free(badWord);
#else
	if((long)data==1)
		aspell_speller_add_to_session(spellChecker,badWord,-1);
	else
		{
			aspell_speller_add_to_personal(spellChecker,badWord,-1);
			aspell_speller_save_all_word_lists(spellChecker);
		}

	((QDialog*)spellCheckWord)->done(0);

	if(badWord!=NULL)
		g_free(badWord);
#endif
}

void doSpellCheckDoc(Widget* widget,void* data)
{
	AspellCanHaveError*		ret;
	AspellDocumentChecker*	checker;
	AspellToken				token;
	int						diff;
	unsigned int			goodwordlen;
	char*					word_begin;
	char*					badword;
	char*					line;

#ifndef _USEQT5_
	GtkTextIter				start;
	GtkTextIter				end;
	GtkTextIter				startiter;
	GtkTextIter				enditer;

	gtk_text_buffer_get_start_iter((GtkTextBuffer*)bufferBox,&startiter);
	gtk_text_buffer_get_end_iter((GtkTextBuffer*)bufferBox,&enditer);

	line=gtk_text_buffer_get_text((GtkTextBuffer*)bufferBox,&startiter,&enditer,false);
#else
	QString	qstr;

	qstr=((QPlainTextEdit*)bufferBox)->toPlainText();
	QByteArray byteArray=qstr.toUtf8();
	line=(char*)byteArray.constData();
#endif
	/* Set up the document checker */
	ret=new_aspell_document_checker(spellChecker);
	if (aspell_error(ret)!=0)
		{
			printf("Error: %s\n",aspell_error_message(ret));
			return;
		}

	checker=to_aspell_document_checker(ret);
	  /* First process the line */
	aspell_document_checker_process(checker,line,-1);
	diff=0;
	  /* Now find the misspellings in the line */
	while(token=aspell_document_checker_next_misspelling(checker),token.len!=0)
		{
	    /* Pay particular attention to how token.offset and diff is used */
			asprintf(&badword,"%.*s",token.len,(char*)&line[token.offset+diff]);
			goodWord=NULL;
			checkTheWord(badword,1);
			if(cancelCheck==true)
				{
					delete_aspell_document_checker(checker);
					return;
				}
			word_begin=line+token.offset+diff;

			if(goodWord!=NULL)
				{
					goodwordlen=strlen(goodWord);
	    /* Replace the misspelled word with the replacement */
					diff+=goodwordlen-token.len;
					memmove(word_begin+goodwordlen,word_begin+token.len,strlen(word_begin+token.len)+1);
					memcpy(word_begin,goodWord,goodwordlen);
				}
			}

	delete_aspell_document_checker(checker);
//replace all text in check document
#ifndef _USEQT5_

	gtk_text_buffer_get_bounds((GtkTextBuffer*)bufferBox,&start,&end);
	gtk_text_buffer_select_range((GtkTextBuffer*)bufferBox,&start,&end);
	gtk_text_buffer_delete_selection((GtkTextBuffer*)bufferBox,true,true);
	gtk_text_buffer_get_start_iter((GtkTextBuffer*)bufferBox,&start);
	gtk_text_buffer_insert((GtkTextBuffer*)bufferBox,&start,line,-1);

	if(spellCheckWord!=NULL)
		{
			gtk_widget_destroy(spellCheckWord);
			spellCheckWord=NULL;
		}
#else
	((QPlainTextEdit*)bufferBox)->setPlainText(line);
#endif
}
