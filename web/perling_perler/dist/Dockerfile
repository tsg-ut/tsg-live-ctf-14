FROM perl:5.36

WORKDIR /app

RUN cpanm -n Dancer2 Template

RUN useradd -m -s /bin/bash appuser
COPY app/ .
RUN chmod 444 ./app.pl && \
  chmod 555 ./views && \
  chmod 444 ./views/index.tt
USER appuser

CMD ["perl", "app.pl"]
