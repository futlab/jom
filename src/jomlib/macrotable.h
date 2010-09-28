/****************************************************************************
 **
 ** Copyright (C) 2008-2010 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the jom project on Trolltech Labs.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 or 3.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
 ** http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/
#pragma once

#include <QtCore/QSet>
#include <QtCore/QStringList>

namespace NMakeFile {

class MacroTable
{
public:
    MacroTable();
    ~MacroTable();

    void setEnvironment(const QStringList& e) { m_environment = e; }
    const QStringList& environment() const { return m_environment; }

    bool isMacroDefined(const QString& name) const;
    bool isMacroNameValid(const QString& name) const;
    QString macroValue(const QString& macroName) const;
    void defineEnvironmentMacroValue(const QString& name, const QString& value, bool readOnly = false);
    void setMacroValue(const QString& name, const QString& value);
    void undefineMacro(const QString& name);
    QString expandMacros(const QString& str) const;
    void dump() const;

    static void parseSubstitutionStatement(const QString &str, int substitutionStartIdx, QString &value, int &macroInvokationEndIdx);

private:
    struct MacroData
    {
        MacroData()
            : isEnvironmentVariable(false), isReadOnly(false)
        {}

        bool isEnvironmentVariable;
        bool isReadOnly;
        QString value;
    };

    MacroData* internalSetMacroValue(const QString& name, const QString& value);
    void setEnvironmentVariable(const QString& name, const QString& value);
    QString expandMacros(const QString& str, QSet<QString>& usedMacros) const;
    QString cycleCheckedMacroValue(const QString& macroName, QSet<QString>& usedMacros) const;

    QHash<QString, MacroData>   m_macros;
    QStringList                 m_environment;
};

} // namespace NMakeFile
