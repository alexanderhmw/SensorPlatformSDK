#include "funcmoudlecreator.h"

FuncMoudleCreator::FuncMoudleCreator(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

FuncMoudleCreator::~FuncMoudleCreator()
{

}

void FuncMoudleCreator::on_browseprojectdir_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this, QString("Choose Project Dir"),QString());
    ui.projectdir->setText(path);
    int n=path.size();
    int i=n-1;
    while(i>=0)
    {
        if(path[i]=='/'||path[i]=='\\')
        {
            ui.funcmodulename->setText(path.right(n-i-1));
            break;
        }
        i--;
    }
}

void FuncMoudleCreator::on_browsefunclibrarydirectory_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this, QString("Choose FuncLibrary Dir"),QString());
    ui.funclibrarydir->setText(path);
}

#define WRITELINE(writer,content) writer.write(QString("%1\n").arg(content).toUtf8());

void FuncMoudleCreator::on_create_clicked()
{
	int i,n=nodelist.size();
	QFile reader,writer;
	QString inputfile,outputfile;
	{
		outputfile=QString("%1\\%2_def.h").arg(ui.projectdir->text()).arg(ui.funcmodulename->text());
		outputfiles.push_back(outputfile);

		writer.setFileName(outputfile);
		writer.open(QFile::WriteOnly | QFile::Text);

		WRITELINE(writer,QString("#ifndef %1_DEF_EXPORT_H").arg(ui.funcmodulename->text().toUpper()));
		WRITELINE(writer,QString("#define %1_DEF_EXPORT_H").arg(ui.funcmodulename->text().toUpper()));
		WRITELINE(writer,"\n");
		for(i=0;i<n;i++)
		{
			WRITELINE(writer,QString("struct Q_DECL_EXPORT %1%2PARAMS").arg(ui.funcmodulename->text()).arg(nodelist[i]));
			WRITELINE(writer,"{\n}");
		}
		
	}

	inputfile=QString("%1\\%2func.h").arg(ui.funclibrarydir->text()).arg("nodebase");
	outputfile=QString("%1\\%2.cpp").arg(ui.projectdir->text()).arg(ui.funcmodulename->text());
	reader.setFileName(inputfile);
	reader.open(QFile::ReadOnly | QFile::Text);
	writer.setFileName(outputfile);
	writer.open(QFile::WriteOnly | QFile::Text);

	for(i=0;i<n;i++)
	{
		QFile 
	}
}

void FuncMoudleCreator::on_sensor_clicked(bool checked)
{
    QString nodetype=QString("sensor");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_sensorwidget_clicked(bool checked)
{
    QString nodetype=QString("sensorwidget");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_storage_clicked(bool checked)
{
    QString nodetype=QString("storage");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_storagewidget_clicked(bool checked)
{
    QString nodetype=QString("storagewidget");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_processor_clicked(bool checked)
{
    QString nodetype=QString("processor");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_processorwidget_clicked(bool checked)
{
    QString nodetype=QString("processorwidget");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_fusion_clicked(bool checked)
{
    QString nodetype=QString("fusion");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}

void FuncMoudleCreator::on_fusionwidget_clicked(bool checked)
{
    QString nodetype=QString("fusionwidget");
    if(checked)
    {
        nodelist.push_back(nodetype);
    }
    else
    {
        nodelist.remove(nodelist.indexOf(nodetype));
    }
}
