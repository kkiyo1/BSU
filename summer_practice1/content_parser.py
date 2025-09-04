import os
import sqlite3
import requests
from bs4 import BeautifulSoup

conn = sqlite3.connect("database.db")
cursor = conn.cursor()
cursor.execute("SELECT link FROM articles")
rows = cursor.fetchall()

for i in range(0, len(rows)):
    url = rows[i][0]

    if url.endswith('/'):
        url = url[:-1]

    name = url.split('/')[-1]
    
    response = requests.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    
    article_folder = os.path.join("content", name)
    os.makedirs(article_folder, exist_ok=True)
    
    content_div = soup.find("div", xmlns="http://www.w3.org/1999/xhtml")
    if content_div:
        with open(os.path.join(article_folder, f"{name}.txt"), 'w', encoding='utf-8') as f:
            f.write(str(content_div))
        
        img_tags = content_div.find_all('img')
        for j, img in enumerate(img_tags):
            img_url = img.get('src')
            if not img_url:
                continue
                
            if img_url.startswith('//'):
                img_url = 'https:' + img_url
            elif img_url.startswith('/'):
                img_url = url + img_url
            
            try:
                img_response = requests.get(img_url, stream=True, timeout=10)
                img_response.raise_for_status()
                
                img_name = os.path.join(article_folder, f"image_{j+1}.jpg")
                with open(img_name, 'wb') as img_file:
                    for chunk in img_response.iter_content(8192):
                        img_file.write(chunk)
            except requests.exceptions.Timeout:
                print(f"Таймаут при загрузке изображения: {img_url}")
            except requests.exceptions.RequestException as e:
                print(f"Ошибка при загрузке {img_url}: {str(e)}")

cursor.close()
conn.close()