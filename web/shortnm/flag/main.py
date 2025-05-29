from fastapi import FastAPI, Request
from fastapi.responses import PlainTextResponse

app = FastAPI()

@app.get("/flag")
async def get_flag(request: Request):
    host = request.headers.get("host", "")
    if host == "flag:45654" and request.url.port == 45654:
        return PlainTextResponse("TSGLIVE{Cr3a71ng_7h3_SSRF_pr0bl3m_wa5_d1ff1cul7}")
    return PlainTextResponse("Access denied", status_code=403)
