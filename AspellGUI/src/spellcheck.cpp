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
	spellCheckWord->done(0);
	badWord.clear();
	spellCheckWord=NULL;
	cancelCheck=true;
}

void checkTheWord(QString word,int checkDoc)
{
	int						correct;
	AspellWordList			*suggestions;
	AspellStringEnumeration	*elements;
	const char				*suggestedword;
	int						wordcnt=0;
	char						*labeltext[512];

	correct=aspell_speller_check(spellChecker,qPrintable(word),-1);
	if(!correct)
		{
			badWord=word;
			cancelCheck=false;
			if(spellCheckWord==NULL)
				buildWordCheckQt(checkDoc);
			else
				{
					for(int j=0;j<numWords;j++)
						wordListDropbox->removeItem(0);

					sprintf((char*)&labeltext,"Change <i><b>%s</b></i> to: ",badWord);
					badWordLabel->setText((char*)labeltext);
				}
	
			suggestions=(AspellWordList*)aspell_speller_suggest(spellChecker,qPrintable(word),-1);
			elements=aspell_word_list_elements(suggestions);
			while((suggestedword=aspell_string_enumeration_next(elements))!=NULL)
				{
					wordListDropbox->addItem(suggestedword);
					wordcnt++;
				}
			numWords=wordcnt;

			delete_aspell_string_enumeration(elements);
			spellCheckWord->exec();
		}
}

void checkWord(void)
{
	if(bufferBox->textCursor().hasSelection()==false)
		return;
	checkTheWord(bufferBox->textCursor().selectedText(),0);
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

	aspell_speller_store_replacement(spellChecker,qPrintable(badWord),-1,qPrintable(goodWord),-1);
	spellCheckWord->done(0);
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

	spellCheckWord->done(0);
	badWord.clear();
}

void doSpellCheckDoc(void)
{
	AspellCanHaveError		*ret;
	AspellDocumentChecker	*checker;
	AspellToken				token;
	int						diff;
	unsigned int				goodwordlen;
	char						*word_begin;
	char						*badword;
	char						*line;

	/* Set up the document checker */
	ret=new_aspell_document_checker(spellChecker);
	if (aspell_error(ret)!=0)
		{
			printf("Error: %s\n",aspell_error_message(ret));
			return;
		}

	line=strdup(qPrintable(bufferBox->toPlainText()));
	checker=to_aspell_document_checker(ret);
	  /* First process the line */
	aspell_document_checker_process(checker,line,-1);
	diff=0;
	  /* Now find the misspellings in the line */
	while(token=aspell_document_checker_next_misspelling(checker),token.len!=0)
		{
	    /* Pay particular attention to how token.offset and diff is used */
			asprintf(&badword,"%.*s",token.len,(char*)&line[token.offset+diff]);
			goodWord.clear();
			checkTheWord(badword,1);
			if(cancelCheck==true)
				{
					delete_aspell_document_checker(checker);
					free(line);
					free(badword);
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
				}
			free(badword);
		}

	delete_aspell_document_checker(checker);
//replace all text in check document
	bufferBox->setPlainText(line);
	free(line);
}
