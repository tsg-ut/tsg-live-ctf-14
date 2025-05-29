from fastapi import FastAPI, Query, Request, Response
from fastapi.responses import RedirectResponse, HTMLResponse
from fastapi.templating import Jinja2Templates
import redis
import httpx
import string, random, os

app = FastAPI()
r = redis.Redis(host=os.getenv("REDIS_HOST", "localhost"), port=6379, decode_responses=True)
templates = Jinja2Templates(directory="templates")

def generate_id(length=12):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

@app.get("/", response_class=HTMLResponse)
async def index(request: Request):
    return templates.TemplateResponse("index.html", {"request": request})

@app.get("/shorten")
async def shorten(request: Request, url: str = Query(...), format: str = Query(None)):
    short_id = generate_id()
    r.set(short_id, url)
    
    base_url = str(request.base_url).rstrip("/")
    short_url = f"{base_url}/{short_id}"
    if (format == "json"):
        return {"shorturl": short_url}
    else:
        return templates.TemplateResponse("result.html", {"request": request, "short_url": short_url})

@app.get("/shortem")
async def shortem(request: Request, url: str = Query(...), format: str = Query(None)):
    short_id = generate_id()
    url = 'http://is.gd/create.php?format=json&url='+url
    async with httpx.AsyncClient(follow_redirects=True) as client:
        response = await client.get(url)
    url = response.json()["shorturl"]
    r.set(short_id, url)
    
    base_url = str(request.base_url).rstrip("/")
    short_url = f"{base_url}/{short_id}"
    if (format == "json"):
        return {"shorturl": short_url}
    else:
        return templates.TemplateResponse("result.html", {"request": request, "short_url": short_url})

@app.get("/shortenm")
async def shortenm(url: str = Query(...)):
    short_id = generate_id() 
    url = 'http://localhost:8000/shortem?format=json&url='+url
    async with httpx.AsyncClient(follow_redirects=True) as client:
        response = await client.get(url)
    url = response.json()["shorturl"]
    r.set(short_id, url)
    
    short_id = generate_id() 
    async with httpx.AsyncClient(follow_redirects=True) as client:
        response = await client.get(url)    
    return Response(content=response.content,status_code=response.status_code,media_type=response.headers.get("content-type"))

@app.get("/{short_id}")
async def redirect(short_id: str):
    url = r.get(short_id)
    if url:
        return RedirectResponse(url)
    return HTMLResponse("URL not found", status_code=404)
