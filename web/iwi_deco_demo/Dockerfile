FROM maven:3.9-eclipse-temurin-17 AS builder
WORKDIR /build
COPY pom.xml .
COPY src ./src
RUN mvn clean package -DskipTests

FROM eclipse-temurin:17-jdk-alpine
WORKDIR /app
COPY --from=builder /build/target/*.jar app.jar
RUN chmod 644 app.jar && chown root:root app.jar
RUN adduser -D appuser
USER appuser
ENTRYPOINT ["java", "-jar", "app.jar"]
