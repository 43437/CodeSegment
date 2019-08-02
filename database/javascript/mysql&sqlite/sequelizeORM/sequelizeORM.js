const Sequelize = require('sequelize');

//方法1:单独传递参数
const sequelize = new Sequelize('test', 'root', 'Printmd1', {
    host: 'localhost',
    dialect: 'mariadb', // 'mysql'
    dialectOptions: {
        timezone: 'Etc/GMT-8',
      },
  });

// 方法2: 传递连接 URI
/*
const sequelize = new Sequelize('mariadb://root:Printmd1@localhost:3306/test', {
    dialectOptions: {
        timezone: 'Etc/GMT-8',
  }});
*/

//for sqlite3
/*
const sequelize = new Sequelize({
dialect: 'sqlite',
storage: 'test.db'
});
*/

// for connection test
/*
sequelize
  .authenticate()
  .then(() => {
    console.log('Connection has been established successfully.');
  })
  .catch(err => {
    console.error('Unable to connect to the database:', err);
  });
*/

const Model = Sequelize.Model;
class User extends Model {}
User.init({
  // 属性
  firstName: {
    type: Sequelize.STRING,
    allowNull: false
  },
  lastName: {
    type: Sequelize.STRING
    // allowNull 默认为 true
  }
}, {
  sequelize,
  modelName: 'user'
  // 参数
});

// create table
//User.sync()

//insert
// 创建新用户
User.create({ firstName: "Jane", lastName: "Doe" }).then(jane => {
  console.log("Jane's auto-generated ID:", jane.id);
});

//find
// 查找所有用户
User.findAll().then(users => {
  console.log("All users:", JSON.stringify(users, null, 4));
});

//update
// 将所有没有姓氏的人改为“Doe”
User.update({ lastName: "new update" }, {
  where: {
    id: '2'
  }
}).then(() => {
  console.log("Done");
});

//delete
// 删除所有名为“Jane”的人
User.destroy({
  where: {
    id: '1'
  }
}).then(() => {
  console.log("Done");
});