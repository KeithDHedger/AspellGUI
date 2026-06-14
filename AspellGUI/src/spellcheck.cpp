/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (spellcheck.cpp) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "spellcheck.h"

bool	cancelCheck=false;

void doCancelCheck(void)
{
	QSettings	prefs("KDHedger","AspellGUI");
	prefs.setValue("wordgeom",spellCheckWord->saveGeometry());

	badWord.clear();
	goodWord.clear();
	cancelCheck=true;
	blockFlag=false;
	spellCheckWord->done(0);
}

bool checkTheWord(QString word,int checkDoc)
{
	int						correct;
	AspellWordList			*suggestions=NULL;
	AspellStringEnumeration	*elements=NULL;
	const char				*suggestedword=NULL;
	int						wordcnt=0;
	bool						retval=false;
	
	wordListDropbox->clear();
	correct=aspell_speller_check(spellChecker,qPrintable(word),-1);
	if(correct==0)
		{
			badWord=word;
			cancelCheck=false;
			badWordLabel->setText(QString("Change <i><b>%1</b></i> to: ").arg(badWord));
			suggestions=(AspellWordList*)aspell_speller_suggest(spellChecker,qPrintable(word),-1);
			if(suggestions==NULL)
				return(false);
			elements=aspell_word_list_elements(suggestions);
			if(elements==NULL)
				return(false);
			while((suggestedword=aspell_string_enumeration_next(elements))!=NULL)
				{
					wordListDropbox->addItem(suggestedword);
					wordcnt++;
					suggestedword=NULL;
				}
			if(wordcnt==0)
				return(false);

			numWords=wordcnt;
			retval=true;
			delete_aspell_string_enumeration(elements);
			if(checkDoc==1)
				spellCheckWord->setWindowTitle("Check Document");
			else
				spellCheckWord->setWindowTitle("Check Word");
			spellCheckWord->setGeometry(checkWordGeom);
			spellCheckWord->show();
			while(blockFlag==true)
				qApp->processEvents();
			if(checkDoc==0)
				return(retval);
		}
	return(retval);
}

void checkWord(void)
{
	bool changedword;

	if(bufferBox->textCursor().hasSelection()==false)
		return;
	blockFlag=true;
	changedword=checkTheWord(bufferBox->textCursor().selectedText(),0);
	blockFlag==false;
	spellCheckWord->hide();
	if(goodWord.isEmpty()==false && badWord.isEmpty()==false && changedword==true)
		bufferBox->textCursor().insertText(goodWord);
	checkWordGeom=spellCheckWord->geometry();
}

void doChangeWord(int data)
{
	QString	qstr;
	QByteArray byteArray;
	const char* str;
	if(data==0)
		{
			if(bufferBox->textCursor().hasSelection()==true)
				{
					qstr=bufferBox->textCursor().selectedText();
					QByteArray byteArray=qstr.toUtf8();
					str=(char*)byteArray.constData();
					if(str==NULL)
						return;
					else
						badWord=strdup(str);
				}
			goodWord=wordListDropbox->currentText();
			bufferBox->textCursor().insertText(goodWord);
			qApp->processEvents();
		}
	else
		{
			goodWord=wordListDropbox->currentText();
		}

	blockFlag=false;
	checkWordGeom=spellCheckWord->geometry();
}

void doAddIgnoreWord(int data)
{
	if(data==1)
		aspell_speller_add_to_session(spellChecker,qPrintable(badWord),-1);
	else
		{
			aspell_speller_add_to_personal(spellChecker,qPrintable(badWord),-1);
			aspell_speller_save_all_word_lists(spellChecker);
		}

	badWord.clear();
	blockFlag=false;
}

void doSpellCheckDoc(void)
{
	QTextCursor				cursor;
	AspellCanHaveError		*ret;
	AspellDocumentChecker	*checker;
	AspellToken				token;
	int						diff;
	unsigned int				goodwordlen;
	char						*word_begin;
	char						*line=NULL;
	int						buffdiff=0;

	/* Set up the document checker */
	if(spellChecker==NULL)
		return;
	ret=new_aspell_document_checker(spellChecker);
	if (aspell_error(ret)!=0)
		{
			printf("Error: %s\n",aspell_error_message(ret));
			return;
		}

	line=strdup(qPrintable(bufferBox->toPlainText()));
	if(line==NULL)
		return;
	checker=to_aspell_document_checker(ret);
	  /* First process the line */
	aspell_document_checker_process(checker,line,-1);
	diff=0;
	  /* Now find the misspellings in the line */
	while(token=aspell_document_checker_next_misspelling(checker),token.len!=0)
		{
		free(line);
		line=strdup(qPrintable(bufferBox->toPlainText()));
	    /* Pay particular attention to how token.offset and diff is used */
			//asprintf(&badword,"%.*s",token.len,(char*)&line[token.offset+diff]);
			//QString lll=line;
			QString xbadword = QString(line).mid(token.offset + diff, token.len);
			goodWord.clear();
			cursor=bufferBox->textCursor();
			cursor.setPosition(token.offset-buffdiff,QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::NextCharacter,QTextCursor::KeepAnchor,token.len);
			bufferBox->setTextCursor(cursor);
			blockFlag=true;
			spellCheckWord->setGeometry(checkWordGeom);
			checkTheWord(xbadword,1);
			if(cancelCheck==true)
				{
					delete_aspell_document_checker(checker);
					bufferBox->setPlainText(line);
					free(line);
					return;
				}

			word_begin=line+token.offset+diff;
			if(goodWord.isEmpty()==false)
				{
					goodwordlen=goodWord.length();
					/* Replace the misspelled word with the replacement */
					diff+=goodwordlen-token.len;
					memmove(word_begin+goodwordlen,word_begin+token.len,strlen(word_begin+token.len)+1);
					memcpy(word_begin,qPrintable(goodWord),goodwordlen);
					bufferBox->setPlainText(line);
					buffdiff+=badWord.length()-goodWord.length();
				}
		}

	delete_aspell_document_checker(checker);
//replace all text in check document
	bufferBox->setPlainText(line);
	free(line);
	checkWordGeom=spellCheckWord->geometry();
	doCancelCheck();
}
