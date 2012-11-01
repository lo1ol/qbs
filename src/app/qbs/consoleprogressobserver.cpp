/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Build Suite.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/
#include "consoleprogressobserver.h"

#include <QString>

#include <iostream>

namespace qbs {

void ConsoleProgressObserver::initialize(const QString &task, int max)
{
    m_maximum = max;
    m_value = 0;
    m_percentage = 0;
    std::cout << task.toLocal8Bit().constData() << ": 0%" << std::flush;
}

void ConsoleProgressObserver::setProgressValue(int value)
{
    if (value > m_maximum || value <= m_value)
        return; // TODO: Should be an assertion, but the executor currently breaks it.
    m_value = value;
    const int newPercentage = (100 * m_value) / m_maximum;
    if (newPercentage == m_percentage)
        return;
    eraseCurrentPercentageString();
    m_percentage = newPercentage;
    updateProgressBarIfNecessary();
    writePercentageString();
    if (m_value == m_maximum)
        std::cout << std::endl;
    else
        std::cout << std::flush;
}

void ConsoleProgressObserver::eraseCurrentPercentageString()
{
    const int charsToErase = m_percentage == 0 ? 2 : m_percentage < 10 ? 3 : 4;

    // (1) Move cursor before the old percentage string.
    // (2) Erase current line content to the right of the cursor.
    std::cout << QString::fromLocal8Bit("\x1b[%1D").arg(charsToErase).toLocal8Bit().constData();
    std::cout << "\x1b[K";
}

void ConsoleProgressObserver::updateProgressBarIfNecessary()
{
    static const int TotalHashCount = 50; // Should fit on most terminals without a line break.
    if ((m_percentage % (100 / TotalHashCount)) == 0)
        std::cout << "#";
}

void ConsoleProgressObserver::writePercentageString()
{
    std::cout << QString::fromLocal8Bit(" %1%").arg(m_percentage).toLocal8Bit().constData();
}

} // namespace qbs
