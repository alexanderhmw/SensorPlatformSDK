#include "xmlparamsloader.h"

#define NODECLASS "Class"
#define NODENAME "Name"
#define VALUETYPE "ValueType"
#define DATATYPE "DataType"
#define VALUEBASE "Base"

XMLParamsLoader::XMLParamsLoader()
{

}

XMLParamsLoader::~XMLParamsLoader()
{

}

bool XMLParamsLoader::loadParams(QString configfilename, QString nodetype, QString nodeclass, QString nodename)
{
	_paramnames.clear();
	_paramcontents.clear();
	QFile file(configfilename);
	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		return 0;
	}
	QXmlStreamReader reader;
	reader.setDevice(&file);
	bool flag=0;
	while(!reader.atEnd())
	{
		if(reader.isStartElement())
		{
			if(reader.name()==nodetype&&reader.attributes().value(NODECLASS)==nodeclass&&reader.attributes().value(NODENAME)==nodename)
			{
				flag=loadContents(reader);
				break;
			}
		}
		reader.readNext();
	}
	reader.clear();
	file.close();
	return flag;
}

bool XMLParamsLoader::loadContents(QXmlStreamReader & reader)
{
	bool flag=0;

	QString nodestart=reader.name().toString();
	reader.readNext();
	while(!reader.atEnd())
	{
		if(reader.isStartElement())
		{
			_paramnames.push_back(reader.name().toString());
			ParamContent tempcontent;
			tempcontent.valuetype=reader.attributes().value(VALUETYPE).toString();
			tempcontent.datatype=reader.attributes().value(DATATYPE).toString();
			if(reader.attributes().hasAttribute(VALUEBASE))
			{
				tempcontent.valuebase=reader.attributes().value(VALUEBASE).toString().toInt();
			}
			else
			{
				tempcontent.valuebase=10;
			}
			QString paramstart=reader.name().toString();
			reader.readNext();			
			while(!reader.atEnd())
			{
				if(reader.isStartElement())
				{
					tempcontent.valuename.push_back(reader.name().toString());
					tempcontent.value.push_back(reader.readElementText());
				}
				else if(reader.isEndElement())
				{
					if(reader.name()==paramstart)
					{
						break;
					}
				}
				reader.readNext();
			}
			_paramcontents.push_back(tempcontent);
		}
		else if(reader.isEndElement())
		{
			if(reader.name()==nodestart)
			{
				flag=1;
				break;
			}
		}
		reader.readNext();
	}
	return flag;
}

bool XMLParamsLoader::getParam(QString name, int & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toInt(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, unsigned int & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toUInt(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, short & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toShort(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, unsigned short & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toUShort(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, long & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toLong(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, unsigned long & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag;
	param=_paramcontents[index].value.back().toULong(&flag,_paramcontents[index].valuebase);
	return 1;
}

bool XMLParamsLoader::getParam(QString name, float & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	param=_paramcontents[index].value.back().toFloat();
	return 1;
}

bool XMLParamsLoader::getParam(QString name, double & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	param=_paramcontents[index].value.back().toDouble();
	return 1;
}

bool XMLParamsLoader::getParam(QString name, std::string & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	param=_paramcontents[index].value.back().toStdString();
	return 1;
}

bool XMLParamsLoader::getParam(QString name, QString & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	param=_paramcontents[index].value.back();
	return 1;
}

bool XMLParamsLoader::getParam(QString name, QByteArray & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	switch(_paramcontents[index].valuebase)
	{
	case 10:
		param=_paramcontents[index].value.back().toAscii();
		break;
	case 16:
		{
			QString tempqstr="0x";
			int hexindex=_paramcontents[index].value.back().indexOf(tempqstr);
			if(hexindex==0)
			{
				tempqstr=_paramcontents[index].value.back().right(_paramcontents[index].value.back().size()-2);
			}
			else
			{
				return 0;
			}
			param=QByteArray::fromHex(tempqstr.toAscii());
		}		
		break;
	default:
		return 0;
		break;
	}
	return 1;
}