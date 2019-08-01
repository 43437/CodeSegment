from peewee import *
from datetime import *
import copy

# 连接数据库
#database = MySQLDatabase('test', user='root', host='localhost', password='xxxx', port=3306)    //for mysql
database = SqliteDatabase('test.db')        //for sqlite

# 定义Person
class Person(Model):
    name = CharField()
    birthday = DateField()
    is_relative = BooleanField()

    class Meta:
        database = database

# 0. 创建表
#Person.create_table()

# 1. 增
# 添加一条数据
p = Person(name='liuchungui', birthday=date(1990, 12, 20), is_relative=True)
p.save()

p = Person(name='name', birthday=date(1990, 12, 20), is_relative=True)
p.save()

# 2. 删
# 删除姓名为perter的数据
Person.delete().where(Person.name == 'perter').execute()

# 已经实例化的数据, 使用delete_instance
p = Person(name='liuchungui', birthday=date(1990, 12, 20), is_relative=False)
p.id = 1
p.save()
p.delete_instance()

# 3. 改
# 已经实例化的数据,指定了id这个primary key,则此时保存就是更新数据
p = Person(name='liuchungui', birthday=date(1990, 12, 20), is_relative=False)
p.id = 1
p.save()

# 更新birthday数据
q = Person.update({Person.birthday: date(1983, 12, 21)}).where(Person.name == 'liuchungui')
q.execute()

# 4. 查
# 使用where()查询
px = Person.select().where(Person.name == 'name8')
for x in px:
    print("x->", x.name, x.birthday, x.is_relative)
#print(px.name, px.birthday, px.is_relative)

