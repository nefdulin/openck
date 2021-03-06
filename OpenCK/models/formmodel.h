/*
** formmodel.h
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 18-Jul-2017
*/

//!@file formmodel.h Header for the form view model and its items.

#ifndef FORMMODEL_H
#define FORMMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QVariant>
#include <QList>
#include <QObject>

#include "form.h"
#include "tes4form.h"
#include "gmstform.h"
#include "colorform.h"

namespace Models
{
    class FormModelItem;
    class FormModel;
}

/**
 * The class for items in the file model.
 * @brief The class for items in the File Model.
 * @see FileModel
 */
class FormModelItem : public QObject
{
    Q_OBJECT

public:
    explicit FormModelItem(const QVector<QVariant> &data, FormModelItem* parent = 0);
    ~FormModelItem();

    FormModelItem* child(int number);
    FormModelItem* parent();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

    /**
     * Full form structure, to be stored in database.
     * @brief formData Form data structure.
     */
    Form* formData;
    /**
     * List of child items belonging to the current item.
     * @brief childItems List of child items.
     */
    QList<FormModelItem*> childItems;

private:
    /**
     * Dynamic array containing data entries for current item.
     * @brief itemData Vector of data entries.
     */
    QVector<QVariant> itemData;
    /**
     * Pointer to parent item. This is null if the item is a root node.
     * @brief parentItem Pointer to parent item.
     */
    FormModelItem* parentItem;
};

/**
 * The view model from which all files and their records are viewed.
 * @brief The view model for files in the UI.
 */
class FormModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    FormModel(const QStringList &headers, QObject* parent = 0);
    ~FormModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    FormModelItem* getItem(const QModelIndex &index) const;

public slots:
    void readForm(Form* form, QString name);

private:
    void readTES4(TES4Form* TES4);
    void readGMST(GMSTForm* GMST);
    void readColor(ColorForm* color);
    void readFormHeader(FormHeader* header);
    FormModelItem* insertFormHeader(FormHeader* header, int fileNumber);
    /**
     * Root item of the data model.
     * @brief Root of model.
     */
    FormModelItem* rootItem;
};

#endif // FILEMODEL_H
