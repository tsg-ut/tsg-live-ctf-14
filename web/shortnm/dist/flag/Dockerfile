FROM python:3.11-slim

WORKDIR /app

COPY ./main.py .

RUN useradd -m -s /bin/bash appuser
RUN pip install --no-cache-dir fastapi uvicorn
RUN chmod 444 ./main.py
EXPOSE 45654
USER appuser

ENTRYPOINT ["uvicorn"]
CMD ["main:app", "--host", "0.0.0.0", "--port", "45654"]
