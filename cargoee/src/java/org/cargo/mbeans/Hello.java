package org.cargo.mbeans;

import javax.inject.Named;
import javax.enterprise.context.SessionScoped;
import java.io.Serializable;
import java.sql.Connection;
import java.sql.ResultSet;
import javax.annotation.Resource;
import javax.sql.DataSource;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.cargo.interceptors.Audit;

@Named(value = "hello")
@SessionScoped
public class Hello implements Serializable {

    private static final Logger log = LogManager.getLogger(Hello.class);

    @Resource(name = "java:/jdbc/cargoDS")
    private DataSource ds;
    private String name;

    public Hello() {
        name = "jorgito";
    }

    @Audit
    public String getName() throws Exception {
        log.info("-----> Inicio");
        Connection con = ds.getConnection();
        ResultSet rs = con.prepareStatement("select now()").executeQuery();
        while (rs.next()) {
            log.info("\t\t(now): " + rs.getObject(1).toString());
        }
        rs.close();
        con.close();
        log.info("<----- Fin");
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
