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
	bool flag=1;
	param=_paramcontents[index].value.back().toInt(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, unsigned int & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toUInt(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, short & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toShort(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, unsigned short & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toUShort(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, long & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toLong(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, unsigned long & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toULong(&flag,_paramcontents[index].valuebase);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, float & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toFloat(&flag);
	return flag;
}

bool XMLParamsLoader::getParam(QString name, double & param)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	bool flag=1;
	param=_paramcontents[index].value.back().toDouble(&flag);
	return flag;
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
		param=_paramcontents[index].value.back().toUtf8();
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
			param=QByteArray::fromHex(tempqstr.toUtf8());
		}		
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

bool XMLParamsLoader::getValueNameList(QString name, QVector<QString> & valuenames)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].valuename.size();
	valuenames=_paramcontents[index].valuename.mid(0,n-1);
	return 1;
}

bool XMLParamsLoader::getValueList(QString name, QVector<int> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toInt(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<unsigned int> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toUInt(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<short> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toShort(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<unsigned short> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toUShort(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<long> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toLong(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<unsigned long> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toULong(&tempflag,_paramcontents[index].valuebase);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<float> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toFloat(&tempflag);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<double> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	bool flag=1;
	for(int i=0;i<n;i++)
	{
		bool tempflag;
		values[i]=_paramcontents[index].value[i].toDouble(&tempflag);
		flag&=tempflag;
	}
	return flag;
}

bool XMLParamsLoader::getValueList(QString name, QVector<std::string> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	for(int i=0;i<n;i++)
	{
		values[i]=_paramcontents[index].value[i].toStdString();
	}
	return 1;
}

bool XMLParamsLoader::getValueList(QString name, QVector<QString> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size();
	values=_paramcontents[index].value.mid(0,n-1);
	return 1;
}

bool XMLParamsLoader::getValueList(QString name, QVector<QByteArray> & values)
{
	int index=_paramnames.indexOf(name);
	if(index<0)
	{
		return 0;
	}
	int n=_paramcontents[index].value.size()-1;
	values.resize(n);
	for(int i=0;i<n;i++)
	{
		switch(_paramcontents[index].valuebase)
		{
		case 10:
			values[i]=_paramcontents[index].value[i].toUtf8();
			break;
		case 16:
			{
				QString tempqstr="0x";
				int hexindex=_paramcontents[index].value[i].indexOf(tempqstr);
				if(hexindex==0)
				{
					tempqstr=_paramcontents[index].value[i].right(_paramcontents[index].value[i].size()-2);
				}
				else
				{
					return 0;
				}
				values[i]=QByteArray::fromHex(tempqstr.toUtf8());
			}		
			break;
		default:
			return 0;
			break;
		}		
	}
	return 1;
}