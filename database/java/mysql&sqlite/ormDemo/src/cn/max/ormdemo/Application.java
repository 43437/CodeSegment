package cn.max.ormdemo;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

import com.j256.ormlite.dao.Dao;
import com.j256.ormlite.dao.DaoManager;
import com.j256.ormlite.jdbc.JdbcConnectionSource;
import com.j256.ormlite.stmt.PreparedQuery;
import com.j256.ormlite.stmt.QueryBuilder;
import com.j256.ormlite.stmt.SelectArg;
import com.j256.ormlite.stmt.Where;
import com.j256.ormlite.support.ConnectionSource;
import com.j256.ormlite.table.TableUtils;

public class Application {

//	static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mariadb://localhost:3306/test";		//mysql
    static final String LIT_DB_URL = "jdbc:sqlite:test.db";		//sqlite
    
    static final String USER = "root";
    static final String PASS = "xxx";
    
	public static void main(String[] args) throws SQLException, IOException {
		// TODO Auto-generated method stub
		// this uses h2 by default but change to match your database
        //String databaseUrl = "jdbc:h2:mem:account";
        // create a connection source to our database
        ConnectionSource connectionSource = null;
//		connectionSource = new JdbcConnectionSource(DB_URL, USER, PASS);	//mysql
        connectionSource = new JdbcConnectionSource(LIT_DB_URL);	//sqlite
		
        // instantiate the dao
		// instantiate the DAO to handle Account with String id
		Dao<Account,String> accountDao = DaoManager.createDao(connectionSource, Account.class);
//        TableUtils.createTable(connectionSource, Account.class);		//creat table
        
     // create an instance of Account
//        Account account = new Account();
//        account.setName("new name");
//        account.setPassword("new password");
//
//        // persist the account object to the database
//        //1. insert
//        accountDao.create(account);
        
        //2. update
//        Account account = new Account(1, "update name", "update password");		
//        accountDao.update(account);
        
        //3. delete
//        Account account = new Account(1, "delete name", "delete password");		
//        accountDao.delete(account);
        
        //4. query
        QueryBuilder<Account, String> queryBuilder = accountDao.queryBuilder();
        Where<Account, String> where = queryBuilder.where();
        SelectArg selectArg = new SelectArg();
        // where password="?" and id > 1
        where.eq("password", selectArg).and().gt("id", 1);
        
        // prepare it so it is ready for later query or iterator calls
        PreparedQuery<Account> preparedQuery = queryBuilder.prepare();
        
        selectArg.setValue("new password");
        List<Account> lstAccounts = accountDao.query(preparedQuery);
        if (lstAccounts.isEmpty()){
        	System.out.println("query by condition is empty.");
        }
        for ( Account account : lstAccounts){
        	System.out.println("id, name, password: " + account.getId()+", "+account.getName()+", "+account.getPassword());
        	account.setName("query name");
        	account.setPassword("query password");
        	accountDao.update(account);
        }
        
        // close the connection source
        connectionSource.close();
	}

}
