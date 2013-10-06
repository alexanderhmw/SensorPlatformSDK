#ifndef XMLPARAMSLOADER_H
#define XMLPARAMSLOADER_H

#include<qstring.h>
#include<qvector.h>
#include<qfile.h>
#include<qxmlstream.h>

struct ParamContent
{
	QString valuetype;
	QString datatype;
	int valuebase;
	QVector<QString> valuename;
	QVector<QString> value;
};

class XMLParamsLoader
{
public:
	XMLParamsLoader();
	~XMLParamsLoader();
private:
	QVector<QString> _paramnames;
	QVector<ParamContent> _paramcontents;
public:
	bool loadParams(QString configfilename, QString nodetype, QString nodeclass, QString nodename);
private:
	bool loadContents(QXmlStreamReader & reader);
public:
	bool getParam(QString name, int & param);
	bool getParam(QString name, unsigned int & param);
	bool getParam(QString name, short & param);
	bool getParam(QString name, unsigned short & param);
	bool getParam(QString name, long & param);
	bool getParam(QString name, unsigned long & param);
	bool getParam(QString name, float & param);
	bool getParam(QString name, double & param);
	bool getParam(QString name, std::string & param);
	bool getParam(QString name, QString & param);
	bool getParam(QString name, QByteArray & param);
	template<class EnumType>
	bool getEnumParam(QString name, EnumType & param)
	{
		int tempi;
		int flag=getParam(name,tempi);
		if(flag)
		{
			param=EnumType(tempi);
			return 1;
		}
		return 0;
	}
};

#endif // XMLPARAMSLOADER_H
