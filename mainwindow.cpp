#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "LLNode.h"
#include "LinkedList.h"
#include "IndexAddress.h"
#include "BSNode.h"
#include "BST.h"
#include "TrieNode.h"
#include "Trie.h"
#include "Stack.h"
#include "TSNode.h"
#include "TST.h"
#include "HashNode.h"
#include "HashMap.h"

#include <QGridlayout>
#include <QScrollArea>
#include <QTextEdit>

#include <QtDebug>
#include <QString>
#include <QFileDialog>
#include <QDirIterator>
#include <QTextStream>

QString wdir = "D:\\Desktop\\DS\\docs";
QString swfile = "D:\\Desktop\\DS\\StopWords.txt";

QVector<QString> curFiles;

BST<LinkedList<IndexAddress>> * BSTree;
TST<LinkedList<IndexAddress>> * TSTree;
Trie<LinkedList<IndexAddress>> * TrieTree;
HashMap<LinkedList<IndexAddress>> * Hash;

int bmode = 0; //0 BST //1 TST //2 Trie //3 Hash

bool stopwordsEnable = false;
BST<QString> * SW;

void MainWindow::appendLog(QString log , bool withNewLine = true)
{
    if(withNewLine)
        ui->cmdLog->append(log);
    else{
        ui->cmdLog->moveCursor (QTextCursor::End);
        ui->cmdLog->insertPlainText(log);
        ui->cmdLog->moveCursor (QTextCursor::End);
    }

    //Move to end
    QTextCursor c = ui->cmdLog->textCursor();
    c.movePosition(QTextCursor::End);
    ui->cmdLog->setTextCursor(c);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->cmdText,SIGNAL(returnPressed()),this,SLOT(handleCmd()));

    BSTree = new BST<LinkedList<IndexAddress>>;

    appendLog("Inverted Index v1.0");
    appendLog("Developed By : Armin Kazemi - 9431068");
    appendLog("----------------------------");
    appendLog("");
    appendLog("Build Mode : BST");
    appendLog("Stopwords : ON");
    appendLog("use 'help' command to view available commands ! ");
    appendLog("");

    initStopWords();

    /*HashMap<int> * hashTest = new HashMap<int>;
    hashTest->put("key1",1);
    hashTest->put("key2",2);
    hashTest->put("key3",3);
    appendLog(*hashTest->get("key1"));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getFileText(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

void MainWindow::printTree(){

    if(bmode==0){   //BST Mode
		if(BSTree)
        appendLog(BSTree->inOrderPrint());
    }else if(bmode==1){ //TST Mode
		if (TSTree)
		appendLog(TSTree->printHtml());
    }else if(bmode==2){ //Trie Mode
		if (TrieTree)
			appendLog(TrieTree->printHtml());
    }else if(bmode==3){ //Hash Mode
        if (Hash)
            appendLog(Hash->printHtml());
    }
}

void MainWindow::addToTree(QString name){
    //loop through files
    QString fdir = wdir + "\\" + name;
    QString text = getFileText(fdir);

    QRegularExpression re("(\\w+)");
    QRegularExpressionMatchIterator i = re.globalMatch(text);
    QStringList words;
    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        words << word;
    }
    for(int i=0;i<words.count();i++){
        QString word = words.at(i);
        //appendLog("read word : " + word + (SW != NULL && !SW->search(word))  );
        if((SW!=NULL && !SW->search(word))){
            if(bmode==0){   //BST Mode
                BSNode<LinkedList<IndexAddress>> * n = BSTree->search(word);
                if(n==NULL){
                    LinkedList<IndexAddress> * ll = new LinkedList<IndexAddress>;
                    IndexAddress *ia = new IndexAddress(name,i);
                    ll->add(*ia);
                    BSTree->insert(word,*ll);
                    //appendLog("new node created in BST !");
                }else{
                    n->data.add(*(new IndexAddress(name,i)));
                    //appendLog("updated node in BST !");
                }
            }else if(bmode==1){ //TST Mode
                TSNode<LinkedList<IndexAddress>> * n = TSTree->search(word);
                if(n==0){
                    LinkedList<IndexAddress> * ll = new LinkedList<IndexAddress>;
                    IndexAddress *ia = new IndexAddress(name,i);
                    ll->add(*ia);
                    TSTree->insert(word,*ll);
                    //appendLog("new node created in TST !");
                }else{
                    n->data.add(*(new IndexAddress(name,i)));
                    //appendLog("updated node in TST !");
                }
			}
			else if (bmode == 2) { //Trie Mode
				word = word.toLower(); // trie only supports lowercase
				TrieNode<LinkedList<IndexAddress>> * n = TrieTree->search(word);
				if (n == 0) {
					LinkedList<IndexAddress> * ll = new LinkedList<IndexAddress>;
					IndexAddress *ia = new IndexAddress(name, i);
					ll->add(*ia);
					TrieTree->insert(word, *ll);
					//appendLog("new node created in Trie !");
				}
				else {
					n->data.add(*(new IndexAddress(name, i)));
					//appendLog("updated node in Trie !");
				}
			}
			else if (bmode == 3) { //Hash Mode
				HashNode<LinkedList<IndexAddress>> * n = Hash->get(word);
				if (n == 0) {
					LinkedList<IndexAddress> * ll = new LinkedList<IndexAddress>;
					IndexAddress *ia = new IndexAddress(name, i);
					ll->add(*ia);
					Hash->put(word, *ll);
				}
				else {
					n->data.add(*(new IndexAddress(name, i)));
				}
			}
        }
    }
}

void MainWindow::removeFromTree(QString name) {
	if (bmode == 0) {
		BSTree->iterBegin();
		while (BSTree->iterHasNext()) {
			LinkedList<IndexAddress> * ll;
			BSNode<LinkedList<IndexAddress>> * bsnp = BSTree->iterNext();
			ll = &bsnp->data;
			ll->iterBegin();
			while (ll->iterHasNext()) {
				IndexAddress ia;
				LLNode<IndexAddress> * lln = ll->iterNext();
				ia = lln->data;
				if (ia.filename == name) {
					ll->iterDel();
				}
			}
			if (ll->isEmpty()) {
				BSTree->remove(bsnp->key);
			}
		}
	}
}

void MainWindow::searchInTree(QString word) {
	if (bmode == 0) {
		BSNode<LinkedList<IndexAddress>> * node = BSTree->search(word);
		if (node) {
			LinkedList<IndexAddress> * ll = &node->data;
			appendLog("Search Results : ");
			appendLog(*ll);
		}
		else {
			appendLog("No Match Found !");
		}
	}
	else if (bmode == 1) {
		TSNode<LinkedList<IndexAddress>> * node = TSTree->search(word);
		if (node) {
			LinkedList<IndexAddress> * ll = &node->data;
			appendLog("Search Results : ");
			appendLog(*ll);
		}
		else {
			appendLog("No Match Found !");
		}
	}
	else if (bmode == 2) {
		word = word.toLower(); // trie only supports lowercase
		TrieNode<LinkedList<IndexAddress>> * node = TrieTree->search(word);
		if (node) {
			LinkedList<IndexAddress> * ll = &node->data;
			appendLog("Search Results : ");
			appendLog(*ll);
		}
		else {
			appendLog("No Match Found !");
		}
	}
	else if (bmode == 3) {
		HashNode<LinkedList<IndexAddress>> * node = Hash->get(word);
		if (node) {
			LinkedList<IndexAddress> * ll = &node->data;
			appendLog("Search Results : ");
			appendLog(*ll);
		}
		else {
			appendLog("No Match Found !");
		}
	}
}


void MainWindow::initStopWords(){
    //FIX THIS : Destruct previous BST
    SW = new BST<QString>;
    QString swtext = getFileText(swfile);
    QStringList words = swtext.split("\n");
    for(int i=0;i<words.count();i++){
        QString word = words.at(i);
        SW->insert(word,word);
    }
    //appendLog("stopwords count : " + QString::number(words.count()));
}


void MainWindow::handleCmd()
{
    QString cmd = ui->cmdText->text();
    appendLog("> " + cmd);
    ui->cmdText->setText("");
    procCmd(cmd);
}

void MainWindow::procCmd(QString cmd)
{
    QStringList query = cmd.split(QRegExp("\\s"));
    procCmd(query);
}

void MainWindow::procCmd(QStringList cmd)
{
    bool handled = false;

    //help
    if(!QString::compare(cmd.at(0),"help",Qt::CaseInsensitive))
    {
        handled = true;
        QString ta = "<font color=\"darkkhaki\">";
        appendLog("available commands :");
        ta += "setdir<br/>";
        ta += "list<br/>";
        ta += "add<br/>";
        ta += "del<br/>";
		ta += "update<br/>";
        ta += "build<br/>";
        ta += "</font>";
        appendLog(ta);
    }

    //setdir
    if(!QString::compare(cmd.at(0),"setdir",Qt::CaseInsensitive))
    {
        handled = true;
        QString tdir = QFileDialog::getExistingDirectory(this,"Select Directory","C:/");
        if(tdir != ""){
            wdir = tdir;
            appendLog("working directory is set to " + wdir);
        }
        else{
            appendLog("error setting working directory");
        }
    }

    //list
    if(!QString::compare(cmd.at(0),"list",Qt::CaseInsensitive))
    {
        handled = true;
        if(cmd.count()>1){
            if(!QString::compare(cmd.at(1),"-f",Qt::CaseInsensitive)){
                appendLog("printing all text files in the directory :");
                if(wdir != ""){
                    QDirIterator it(wdir,QStringList() << "*.txt",QDir::Files ,QDirIterator::Subdirectories);
                    while (it.hasNext()) {
                        appendLog(it.next());
                    }
                }else{
                     appendLog("please set your working directory");
                }
            }
            else if(!QString::compare(cmd.at(1),"-l",Qt::CaseInsensitive)){
                appendLog("Added Files :");
                for(int r=0;r<curFiles.count();r++){
                    QString suffix;
                    if(r == curFiles.count()-1) suffix = "\n"; else suffix = " , " ;
                    appendLog(curFiles[r] + suffix ,false);
                }
            }
            else if(!QString::compare(cmd.at(1),"-w",Qt::CaseInsensitive)){
                printTree();
            }
        }else{
            appendLog("please specify listing parameter");
        }
    }

    //add
    if(!QString::compare(cmd.at(0),"add",Qt::CaseInsensitive))
    {
        handled = true;
        if(cmd.count()>1){
            if(!QString::compare(cmd.at(1),"-all",Qt::CaseInsensitive)){
                int fc = 0;
                QDirIterator it(wdir,QStringList() << "*.txt",QDir::Files ,QDirIterator::Subdirectories);
                while (it.hasNext()) {
                    addToTree(it.next());
                    fc++;
                }
                appendLog(QString::number(fc) + " file(s) added successfully !");
            }else{
                QString docpath = wdir + "/" + cmd.at(1);

                QFileInfo check_file(docpath);
                if (check_file.exists() && check_file.isFile()) {
                    if(docpath.endsWith(".txt")){
                        //do stuff
                        curFiles.append(cmd.at(1));
                        addToTree(cmd.at(1));
                        appendLog(cmd.at(1)+ " added successfully !");
                    }else{
                        appendLog("file must be in .txt format !");
                    }
                } else {
                    appendLog("invalid filename !");
                }
            }
        }else{
            appendLog("please specify document name !");
        }
    }

    //del
    if(!QString::compare(cmd.at(0),"del",Qt::CaseInsensitive))
    {
        handled = true;
        if(cmd.count()>1){
            int delindex = -1;
            for(int r=0;r<curFiles.count();r++){
                if(curFiles.at(r) == cmd.at(1)){
                    delindex = r;
                    break;
                }
            }
            if(delindex == -1){
                appendLog(cmd.at(1)+ " doenst exist in added files !");
            }else{
                curFiles.remove(delindex);
				removeFromTree(cmd.at(1));
                appendLog(cmd.at(1)+ " successfully deleted !");
            }
        }else{
            appendLog("please specify document name !");
        }
    }

	//update
	if (!QString::compare(cmd.at(0), "update", Qt::CaseInsensitive))
	{
		handled = true;
		if (cmd.count()>1) {
			if (!QString::compare(cmd.at(1), "-all", Qt::CaseInsensitive)) {
				for (int r = 0;r<curFiles.count();r++) {
					removeFromTree(curFiles[r]);
					addToTree(curFiles[r]);
				}
				appendLog(QString::number(curFiles.count()) + " file(s) updated successfully !");
			}
			else {
				int updindex = -1;
				for (int r = 0;r<curFiles.count();r++) {
					if (curFiles.at(r) == cmd.at(1)) {
						updindex = r;
						break;
					}
				}
				if (updindex == -1) {
					appendLog(cmd.at(1) + " doenst exist in added files !");
				}
				else {
					removeFromTree(cmd.at(1));
					addToTree(cmd.at(1));
					appendLog(cmd.at(1) + " successfully updated !");
				}
			}
		}
		else {
			appendLog("please specify document name !");
		}
	}	

	//search
	if (!QString::compare(cmd.at(0), "search", Qt::CaseInsensitive))
	{
		handled = true;
		if (cmd.count()>2) {
			if (!QString::compare(cmd.at(1), "-w", Qt::CaseInsensitive)) {
				searchInTree(cmd.at(2));
			}
			else if (!QString::compare(cmd.at(1), "-s", Qt::CaseInsensitive)) {
				
			}
			else {
				appendLog("invalid search parameter !");
			}
		}
		else {
			appendLog("please specify search parameter and expression !");
		}
	}

    //build tree
    if(!QString::compare(cmd.at(0),"build",Qt::CaseInsensitive))
    {
        handled = true;
        if(cmd.count()>1){

            if(cmd.at(1) == "-bst"){
                appendLog("Build Mode : BST");
                bmode = 0;
				if (BSTree != NULL) {
					BSTree->~BST();
					BSTree = NULL;
				}
				if (TSTree != NULL) {
					TSTree->~TST();
					TSTree = NULL;
				}
				if (TrieTree != NULL) {
					TrieTree->~Trie();
					TrieTree = NULL;
				}
				if (Hash != NULL) {
					Hash->~HashMap();
					Hash = NULL;
				}
				BSTree = new BST<LinkedList<IndexAddress>>;

            }else if(cmd.at(1) == "-tst"){
                appendLog("Build Mode : TST");
                bmode = 1;
				if (BSTree != NULL) {
					BSTree->~BST();
					BSTree = NULL;
				}
				if (TSTree != NULL) {
					TSTree->~TST();
					TSTree = NULL;
				}
				if (TrieTree != NULL) {
					TrieTree->~Trie();
					TrieTree = NULL;
				}
				if (Hash != NULL) {
					Hash->~HashMap();
					Hash = NULL;
				}
				TSTree = new TST<LinkedList<IndexAddress>>;

			}
			else if (cmd.at(1) == "-trie") {
				appendLog("Build Mode : Trie");
				bmode = 2;
				if (BSTree != NULL) {
					BSTree->~BST();
					BSTree = NULL;
				}
				if (TSTree != NULL) {
					TSTree->~TST();
					TSTree = NULL;
				}
				if (TrieTree != NULL) {
					TrieTree->~Trie();
					TrieTree = NULL;
				}
				if (Hash != NULL) {
					Hash->~HashMap();
					Hash = NULL;
				}
				TrieTree = new Trie<LinkedList<IndexAddress>>;
			}
			else if (cmd.at(1) == "-hash") {
					appendLog("Build Mode : Hash");
					bmode = 3;
					if (BSTree != NULL) {
						BSTree->~BST();
						BSTree = NULL;
					}
					if (TSTree != NULL) {
						TSTree->~TST();
						TSTree = NULL;
					}
					if (TrieTree != NULL) {
						TrieTree->~Trie();
						TrieTree = NULL;
					}
					if (Hash != NULL) {
						Hash->~HashMap();
						Hash = NULL;
					}
					Hash = new HashMap<LinkedList<IndexAddress>>;

            }else{
                appendLog("invalid build method !");
            }

        }else{
            appendLog("please specify build method !");
        }
    }

    //test
    if(!QString::compare(cmd.at(0),"test",Qt::CaseInsensitive))
    {
        handled = true;
        if(cmd.count()>1){

            if(cmd.at(1) == "-1"){
                appendLog("TESTING LINKED LIST !");

            }else if(cmd.at(1) == "-2"){
                //appendLog("Building Trinary Search Tree :");

            }else if(cmd.at(1) == "-3"){
                //appendLog("Building Trie Search Tree :");

            }else{
                appendLog("invalid test case !");
            }

        }else{
            appendLog("please specify build method !");
        }
    }

    if(!handled) appendLog("unknown command");
    appendLog("");
}
