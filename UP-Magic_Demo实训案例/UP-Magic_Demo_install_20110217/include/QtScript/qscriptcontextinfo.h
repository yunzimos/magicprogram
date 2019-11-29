/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtScript module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. 
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QSCRIPTCONTEXTINFO_H
#define QSCRIPTCONTEXTINFO_H

#include <QtCore/qobjectdefs.h>

#ifndef QT_NO_SCRIPT

#include <QtCore/qlist.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Script)

class QScriptContext;
#ifndef QT_NO_DATASTREAM
class QDataStream;
#endif

class QScriptContextInfoPrivate;
class Q_SCRIPT_EXPORT QScriptContextInfo
{
public:
#ifndef QT_NO_DATASTREAM
    friend Q_SCRIPT_EXPORT QDataStream &operator<<(QDataStream &, const QScriptContextInfo &);
    friend Q_SCRIPT_EXPORT QDataStream &operator>>(QDataStream &, QScriptContextInfo &);
#endif

    enum FunctionType {
        ScriptFunction,
        QtFunction,
        QtPropertyFunction,
        NativeFunction
    };

    QScriptContextInfo(const QScriptContext *context);
    QScriptContextInfo(const QScriptContextInfo &other);
    QScriptContextInfo();
    ~QScriptContextInfo();

    QScriptContextInfo &operator=(const QScriptContextInfo &other);

    bool isNull() const;

    qint64 scriptId() const;
    QString fileName() const;
    int lineNumber() const;
    int columnNumber() const;

    QString functionName() const;
    FunctionType functionType() const;

    QStringList functionParameterNames() const;

    int functionStartLineNumber() const;
    int functionEndLineNumber() const;

    int functionMetaIndex() const;

    bool operator==(const QScriptContextInfo &other) const;
    bool operator!=(const QScriptContextInfo &other) const;

private:
    QScriptContextInfoPrivate *d_ptr;

    Q_DECLARE_PRIVATE(QScriptContextInfo)
};

typedef QList<QScriptContextInfo> QScriptContextInfoList;

#ifndef QT_NO_DATASTREAM
Q_SCRIPT_EXPORT QDataStream &operator<<(QDataStream &, const QScriptContextInfo &);
Q_SCRIPT_EXPORT QDataStream &operator>>(QDataStream &, QScriptContextInfo &);
#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_SCRIPT

#endif
