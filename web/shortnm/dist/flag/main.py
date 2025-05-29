from fastapi import FastAPI, Request
from fastapi.responses import PlainTextResponse

app = FastAPI()

@app.get("/flag")
async def get_flag(request: Request):
    host = request.headers.get("host", "")
    if host == "flag:45654" and request.url.port == 45654:
        return PlainTextResponse("TSGLIVE{REDACTED}")
    return PlainTextResponse("Access denied", status_code=403)
