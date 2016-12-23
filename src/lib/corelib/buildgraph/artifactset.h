/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qbs.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QBS_ARTIFACTSET_H
#define QBS_ARTIFACTSET_H

#include <QStringList>
#include <QVector>

namespace qbs {
namespace Internal {

class Artifact;
class NodeSet;

class ArtifactSet
{
public:
    using const_iterator = QVector<Artifact *>::const_iterator;
    using iterator = QVector<Artifact *>::iterator;
    using value_type = Artifact*;

    iterator begin() { return m_data.begin(); }
    iterator end() { return m_data.end(); }
    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }
    const_iterator cbegin() const { return m_data.cbegin(); }
    const_iterator cend() const { return m_data.cend(); }
    const_iterator constBegin() const { return cbegin(); }
    const_iterator constEnd() const { return cend(); }

    void insert(Artifact *artifact);
    void operator+=(Artifact *artifact) { insert(artifact); }
    void operator<<(Artifact *artifact) { insert(artifact); }

    void clear() { m_data.clear(); }
    void reserve(int size) { m_data.reserve(size); }

    bool remove(Artifact *artifact) { return m_data.removeOne(artifact); }
    void operator-=(Artifact *artifact) { remove(artifact); }

    bool contains(Artifact *artifact) const { return m_data.contains(artifact); }
    bool isEmpty() const { return m_data.isEmpty(); }
    int count() const { return m_data.count(); }

    ArtifactSet &unite(const ArtifactSet &other);
    void operator+=(const ArtifactSet &other) { unite(other); }

    QStringList toStringList() const;
    QString toString() const;

    static ArtifactSet fromNodeSet(const NodeSet &nodes);
    static ArtifactSet fromNodeList(const QList<Artifact *> &lst);

    bool operator==(const ArtifactSet &other) const { return m_data == other.m_data; }
    bool operator!=(const ArtifactSet &other) const { return m_data != other.m_data; }

private:
    QVector<Artifact *> m_data;
};

ArtifactSet operator-(const ArtifactSet &set1, const ArtifactSet &set2);

} // namespace Internal
} // namespace qbs

#endif // QBS_ARTIFACTSET_H
