#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configfile.setFileName(QString("config.xml"));
    this->on_load_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseprojectdir_clicked()
{
    ui->projectdir->setText(QFileDialog::getExistingDirectory(this,QString("Open Project Dir"),QString()));
}

void MainWindow::on_browsefunclibrarydir_clicked()
{
    ui->funclibrarydir->setText(QFileDialog::getExistingDirectory(this,QString("Open FuncLibrary Dir"),QString()));
}

void MainWindow::on_load_clicked()
{
    QXmlStreamReader reader;
	if(!configfile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,QString("Config Error"),QString("No config.xml"));
        exit(0);
    }
	ui->nodelist->clear();
	ui->nodewidgetlist->clear();
    reader.setDevice(&configfile);
    int level=0;
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            level++;
            if(level==2)
            {
                QString nodetype;
                QListWidgetItem * item;

                nodetype=reader.name().toString();
                item=new QListWidgetItem(nodetype,ui->nodelist);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(Qt::Checked);

                nodetype=reader.name().toString()+QString("Widget");
                item=new QListWidgetItem(nodetype,ui->nodewidgetlist);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(Qt::Checked);
            }
        }
        else if(reader.isEndElement())
        {
            level--;
        }
        reader.readNext();
    }
	reader.clear();
	configfile.close();
}

struct NODESTRUCT
{
    QString value;
    QString name;
    QString comment;
};

struct NODEFUNC
{
    QString filesuffix;
    QString funclibrary;
    QString comment;
};

struct NODESTATE
{
    QString nodetype;
    bool withwidget;
    QVector<NODESTRUCT> nodestruct;
    QVector<NODEFUNC> nodefunc;
    QVector<NODESTRUCT> widgetstruct;
    QVector<NODEFUNC> widgetfunc;
};

#define NODESTRUCTTAG "nodestruct"
#define NODEFUNCTAG "nodefunc"
#define WIDGETSTRUCTTAG "widgetstruct"
#define WIDGETFUNCTAG "widgetfunc"
#define COMMENT "comment"

void MainWindow::on_create_clicked()
{
    int i,n=ui->nodelist->count();
    QListWidgetItem * item1,* item2;
    QVector<NODESTATE> nodestate;
    NODESTATE tempstate;
    for(i=0;i<n;i++)
    {
        item1=ui->nodelist->item(i);
        item2=ui->nodewidgetlist->item(i);
        if(item1->checkState()==Qt::Unchecked)
        {
            item2->setCheckState(Qt::Unchecked);
            continue;
        }
        tempstate.nodetype=item1->text();
        if(item2->checkState()==Qt::Checked)
        {
            tempstate.withwidget=1;
        }
        else
        {
            tempstate.withwidget=0;
        }
        nodestate.push_back(tempstate);
    }    
    
    QXmlStreamReader reader;
	if(!configfile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,QString("Config Error"),QString("No config.xml"));
        exit(0);
    }
    reader.setDevice(&configfile);
    i=0;
	n=nodestate.size();
    int level=0;
    bool flag=0;
    int areanum=0;
    while(i<n&&!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            level++;
            switch(level)
            {
            case 2:
                if(reader.name()==nodestate[i].nodetype)
                {
                    flag=1;
                }
                break;
            case 3:
                if(reader.name()==NODESTRUCTTAG)
                {
                    areanum=0;
                }
                else if(reader.name()==NODEFUNCTAG)
                {
                    areanum=1;
                }
                else if(reader.name()==WIDGETSTRUCTTAG)
                {
                    areanum=2;
                }
                else if(reader.name()==WIDGETFUNCTAG)
                {
                    areanum=3;
                }
                break;
            case 4:
                if(flag)
                {
                    switch(areanum)
                    {
                    case 0:
                        {
                            NODESTRUCT nodestruct;
                            nodestruct.value=reader.name().toString();
                            nodestruct.comment=reader.attributes().value(COMMENT).toString();
                            nodestruct.name=reader.readElementText();
                            level--;
                            nodestate[i].nodestruct.push_back(nodestruct);
                        }
                        break;
                    case 1:
                        {
                            NODEFUNC nodefunc;
                            nodefunc.filesuffix=reader.name().toString();
                            nodefunc.comment=reader.attributes().value(COMMENT).toString();
                            nodefunc.funclibrary=reader.readElementText();
                            level--;
                            nodestate[i].nodefunc.push_back(nodefunc);
                        }
                        break;
                    case 2:
                        {
                            NODESTRUCT nodestruct;
                            nodestruct.value=reader.name().toString();
                            nodestruct.comment=reader.attributes().value(COMMENT).toString();
                            nodestruct.name=reader.readElementText();
                            level--;
                            nodestate[i].widgetstruct.push_back(nodestruct);
                        }
                        break;
                    case 3:
                        {
                            NODEFUNC nodefunc;
                            nodefunc.filesuffix=reader.name().toString();
                            nodefunc.comment=reader.attributes().value(COMMENT).toString();
                            nodefunc.funclibrary=reader.readElementText();
                            level--;
                            nodestate[i].widgetfunc.push_back(nodefunc);
                        }
                        break;
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
        else if(reader.isEndElement())
        {
            switch(level)
            {
            case 2:
				if(flag)
				{
					i++;
					flag=0;
				}
                break;
            default:
                break;
            }
            level--;
        }
        reader.readNext();
    }
	reader.clear();
	configfile.close();

	QFile output;
	std::ifstream input;
	QString projectdir=ui->projectdir->text();
	QString funclibrarydir=ui->funclibrarydir->text();
	QString funcmodulename=ui->funcmodulename->text();
	std::string funcbegin=std::string("extern \"C\" Q_DECL_EXPORT ");
	if(n>0)
	{
		QFileInfo fileinfo;
		QString tempfilename;
		
		tempfilename=QString("%1/%2_def.h").arg(projectdir).arg(funcmodulename);
		fileinfo.setFile(tempfilename);
		if(!fileinfo.exists()||QMessageBox::information(this, QString("File Overwrite"),QString("%1 exists, overwrite or not?").arg(tempfilename),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
		{
			output.setFileName(tempfilename);
			output.open(QFile::WriteOnly | QFile::Text);
			output.write(QString("#ifndef %1_DEF_H\n#define %1_DEF_H\n\n#include <QtCore/qglobal.h>\n\n").arg(funcmodulename.toUpper()).toUtf8());
			for(i=0;i<n;i++)
			{
				int j,m=nodestate[i].nodestruct.size();
				for(j=0;j<m;j++)
				{
					output.write(QString("struct Q_DECL_EXPORT %1%2\t//%3\n{\n\n};\n\n").arg(funcmodulename.toUpper()).arg(nodestate[i].nodestruct[j].name).arg(nodestate[i].nodestruct[j].comment).toUtf8());
				}
				if(nodestate[i].withwidget)
				{
					m=nodestate[i].widgetstruct.size();
					for(j=0;j<m;j++)
					{
						output.write(QString("struct Q_DECL_EXPORT %1%2\t//%3\n{\n\n};\n\n").arg(funcmodulename.toUpper()).arg(nodestate[i].widgetstruct[j].name).arg(nodestate[i].widgetstruct[j].comment).toUtf8());
					}
				}
			}
			output.write(QString("#endif").toUtf8());
			output.close();
		}
		tempfilename=QString("%1/%2.h").arg(projectdir).arg(funcmodulename);
		fileinfo.setFile(tempfilename);
		if(!fileinfo.exists()||QMessageBox::information(this, QString("File Overwrite"),QString("%1 exists, overwrite or not?").arg(tempfilename),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
		{			
			output.setFileName(tempfilename);
			output.open(QFile::WriteOnly | QFile::Text);
			output.write(QString("#ifndef %1_H\n#define %1_H\n\n#include \"%2_def.h\"\n\n//Add headers below\n\n#endif").arg(funcmodulename.toUpper()).arg(funcmodulename).toUtf8());
			output.close();	
		}
		tempfilename=QString("%1/%2.cpp").arg(projectdir).arg(funcmodulename);
		fileinfo.setFile(tempfilename);
		if(!fileinfo.exists()||QMessageBox::information(this, QString("File Overwrite"),QString("%1 exists, overwrite or not?").arg(tempfilename),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
		{
			output.setFileName(tempfilename);
			output.open(QFile::WriteOnly | QFile::Text);
			output.write(QString("#include \"%1.h\"\n#include<FuncLibrary\\nodebasefunc.h>\n\n//Add static library below (#pragma comment(lib,\"XXX.lib\")\n\n").arg(funcmodulename).toUtf8());
			input.open(QString("%1/nodebasefunc.h").arg(funclibrarydir).toUtf8().constData());
			std::string tempstr;
			while(std::getline(input,tempstr,'\n'))
			{
				int startpos=tempstr.find(funcbegin);
				if(startpos!=std::string::npos)
				{
					startpos=startpos+funcbegin.size();
					int endpos=tempstr.find(';');
					if(endpos!=std::string::npos)
					{
						int funcsize=endpos-startpos;
						QString func;
						int commentpos=tempstr.find("//");
						if(commentpos!=std::string::npos)
						{
							int commentsize=tempstr.size()-commentpos;
							func=QString("%1\t%2\n{\n\n}\n\n").arg(tempstr.substr(startpos,funcsize).c_str()).arg(tempstr.substr(commentpos,commentsize).c_str());
						}
						else
						{
							func=QString("%1\n{\n\n}\n\n").arg(tempstr.substr(startpos,funcsize).c_str());
						}
						output.write(func.toUtf8());
					}
				}
			}
			input.close();
			input.clear();
			output.close();
		}
	}

	for(i=0;i<n;i++)
	{
		int j,m=nodestate[i].nodefunc.size();
		for(j=0;j<m;j++)
		{
			QFileInfo fileinfo;
			QString tempfilename;

			tempfilename=QString("%1/%2_%3.cpp").arg(projectdir).arg(funcmodulename).arg(nodestate[i].nodefunc[j].filesuffix);
			fileinfo.setFile(tempfilename);
			if(!fileinfo.exists()||QMessageBox::information(this, QString("File Overwrite"),QString("%1 exists, overwrite or not?").arg(tempfilename),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
			{
				output.setFileName(tempfilename);
				output.open(QFile::WriteOnly | QFile::Text);
				output.write(QString("#include \"%1.h\"\n#include<FuncLibrary\\%2>\n\n").arg(funcmodulename).arg(nodestate[i].nodefunc[j].funclibrary).toUtf8());
				input.open(QString("%1/%2").arg(funclibrarydir).arg(nodestate[i].nodefunc[j].funclibrary).toUtf8().constData());
				std::string tempstr;
				while(std::getline(input,tempstr,'\n'))
				{
					int startpos=tempstr.find(funcbegin);
					if(startpos!=std::string::npos)
					{
						startpos=startpos+funcbegin.size();
						int endpos=tempstr.find(';');
						if(endpos!=std::string::npos)
						{
							int funcsize=endpos-startpos;
							QString func;
							int commentpos=tempstr.find("//");
							if(commentpos!=std::string::npos)
							{
								int commentsize=tempstr.size()-commentpos;
								func=QString("%1\t%2\n{\n").arg(tempstr.substr(startpos,funcsize).c_str()).arg(tempstr.substr(commentpos,commentsize).c_str());
							}
							else
							{
								func=QString("%1\n{\n").arg(tempstr.substr(startpos,funcsize).c_str());
							}
							output.write(func.toUtf8());
							int k,l=nodestate[i].nodestruct.size();
							for(k=0;k<l;k++)
							{
								int valuepos=tempstr.find(nodestate[i].nodestruct[k].value.toStdString());
								if(valuepos!=std::string::npos)
								{
									int typepose=valuepos-1;
									int starcount=0;
									while(typepose>=0&&(tempstr[typepose]==' '||tempstr[typepose]=='*'))
									{
										if(tempstr[typepose]=='*')
										{
											starcount++;
										}
										typepose--;
									}
									if(starcount==1)
									{
										output.write(QString("\t%1 * %2%3=(%1 *)%3;\n").arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
									}
									else if(starcount==2)
									{
										output.write(QString("\t%1 * %2%3=(%1 *)(*%3);\n").arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
										output.write(QString("\tif(%1%2==NULL)\n\t{//case1: %2 point to a NULL\n\t\t\n\t\t%1%2=(%3 *)(*%2);\n\t}\n").arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).toUtf8());
										output.write(QString("\telse\n\t{//case2: %2 point to a memory block\n\t\t\n\t}\n").arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
									}
								}
							}
							output.write("}\n\n");
						}
					}
				}
				output.write("//==========================================================\n//Add other functions below and make sure to add (extern \"C\" Q_DECL_EXPORT\) in front of the function in the header\n");
				input.close();
				input.clear();
				output.close();
			}
		}
		if(nodestate[i].withwidget)
		{
			m=nodestate[i].widgetfunc.size();
			for(j=0;j<m;j++)
			{
				QFileInfo fileinfo;
				QString tempfilename;

				tempfilename=QString("%1/%2_%3.cpp").arg(projectdir).arg(funcmodulename).arg(nodestate[i].widgetfunc[j].filesuffix);
				fileinfo.setFile(tempfilename);
				if(!fileinfo.exists()||QMessageBox::information(this, QString("File Overwrite"),QString("%1 exists, overwrite or not?").arg(tempfilename),QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
				{
					output.setFileName(tempfilename);
					output.open(QFile::WriteOnly | QFile::Text);
					output.write(QString("#include \"%1.h\"\n#include<FuncLibrary\\%2>\n\n").arg(funcmodulename).arg(nodestate[i].widgetfunc[j].funclibrary).toUtf8());
					input.open(QString("%1/%2").arg(funclibrarydir).arg(nodestate[i].widgetfunc[j].funclibrary).toUtf8().constData());
					std::string tempstr;
					while(std::getline(input,tempstr,'\n'))
					{
						int startpos=tempstr.find(funcbegin);
						if(startpos!=std::string::npos)
						{
							startpos=startpos+funcbegin.size();
							int endpos=tempstr.find(';');
							if(endpos!=std::string::npos)
							{
								int funcsize=endpos-startpos;
								QString func;
								int commentpos=tempstr.find("//");
								if(commentpos!=std::string::npos)
								{
									int commentsize=tempstr.size()-commentpos;
									func=QString("%1\t%2\n{\n").arg(tempstr.substr(startpos,funcsize).c_str()).arg(tempstr.substr(commentpos,commentsize).c_str());
								}
								else
								{
									func=QString("%1\n{\n").arg(tempstr.substr(startpos,funcsize).c_str());
								}
								output.write(func.toUtf8());
								int k,l=nodestate[i].widgetstruct.size();
								for(k=0;k<l;k++)
								{
									int valuepos=tempstr.find(nodestate[i].widgetstruct[k].value.toStdString());
									if(valuepos!=std::string::npos)
									{
										int typepose=valuepos-1;
										int starcount=0;
										while(typepose>=0&&(tempstr[typepose]==' '||tempstr[typepose]=='*'))
										{
											if(tempstr[typepose]=='*')
											{
												starcount++;
											}
											typepose--;
										}
										if(starcount==1)
										{
											output.write(QString("\t%1 * %2%3=(%1 *)%3;\n").arg(funcmodulename.toUpper()+nodestate[i].widgetstruct[k].name).arg(funcmodulename).arg(nodestate[i].widgetstruct[k].value).toUtf8());
										}
										else if(starcount==2)
										{
											output.write(QString("\t%1 * %2%3=(%1 *)(*%3);\n").arg(funcmodulename.toUpper()+nodestate[i].widgetstruct[k].name).arg(funcmodulename).arg(nodestate[i].widgetstruct[k].value).toUtf8());
											output.write(QString("\tif(%1%2==NULL)\n\t{//case1: %2 point to a NULL\n\t\t\n\t\t%1%2=(%3 *)(*%2);\n\t}\n").arg(funcmodulename).arg(nodestate[i].widgetstruct[k].value).arg(funcmodulename.toUpper()+nodestate[i].widgetstruct[k].name).toUtf8());
											output.write(QString("\telse\n\t{//case2: %2 point to a memory block\n\t\t\n\t}\n").arg(funcmodulename).arg(nodestate[i].widgetstruct[k].value).toUtf8());
										}
									}
								}
								l=nodestate[i].nodestruct.size();
								for(k=0;k<l;k++)
								{
									int valuepos=tempstr.find(nodestate[i].nodestruct[k].value.toStdString());
									if(valuepos!=std::string::npos)
									{
										int typepose=valuepos-1;
										int starcount=0;
										while(typepose>=0&&(tempstr[typepose]==' '||tempstr[typepose]=='*'))
										{
											if(tempstr[typepose]=='*')
											{
												starcount++;
											}
											typepose--;
										}
										if(starcount==1)
										{
											output.write(QString("\t%1 * %2%3=(%1 *)%3;\n").arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
										}
										else if(starcount==2)
										{
											output.write(QString("\t%1 * %2%3=(%1 *)(*%3);\n").arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
											output.write(QString("\tif(%1%2==NULL)\n\t{//case1: %2 point to a NULL\n\t\t\n\t\t%1%2=(%3 *)(*%2);\n\t}\n").arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).arg(funcmodulename.toUpper()+nodestate[i].nodestruct[k].name).toUtf8());
											output.write(QString("\telse\n\t{//case2: %2 point to a memory block\n\t\t\n\t}\n").arg(funcmodulename).arg(nodestate[i].nodestruct[k].value).toUtf8());
										}
									}
								}
								output.write("}\n\n");
							}
						}
					}
					output.write("//==========================================================\n//Add other functions below and make sure to add (extern \"C\" Q_DECL_EXPORT\) in front of the function\n");
					input.close();
					input.clear();
					output.close();
				}
			}
		}
	}
	QMessageBox::information(this,QString("Finish"),QString("All files for %1 have been created. Please add them to the project and add includepath \"SensorPlatformSDK\\Core\"").arg(funcmodulename));
}
