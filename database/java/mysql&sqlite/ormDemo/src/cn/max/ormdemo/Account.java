package cn.max.ormdemo;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "accounts")
public class Account {
	@DatabaseField(generatedId=true)
	private Integer id;
	@DatabaseField
    private String name;
    @DatabaseField
    private String password;
    
    public Account() {
        // ORMLite needs a no-arg constructor 
    }
    public Account(int id, String name, String password) {
    	this.id = id;
        this.name = name;
        this.password = password;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    public int getId(){
    	return this.id;
    }
}
