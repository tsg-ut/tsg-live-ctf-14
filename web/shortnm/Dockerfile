FROM python:3.11-slim
WORKDIR /app
COPY app/ .
RUN useradd -m -s /bin/bash appuser
RUN chmod 555 .
RUN chmod 444 main.py && \
  chmod 444 requirements.txt && \
  chmod 444 templates/index.html && \
  chmod 444 templates/result.html && \
  chmod 555 templates/

RUN pip install --no-cache-dir -r requirements.txt

USER appuser
ENTRYPOINT ["uvicorn"]
CMD ["main:app", "--host", "0.0.0.0", "--port", "8000"]
