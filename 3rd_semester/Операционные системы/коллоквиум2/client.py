import requests
import json
import sys

class TodoClient:
    """Клиент для работы с To-Do API"""
    
    def __init__(self, base_url="http://localhost:8000/api"):
        self.base_url = base_url
        self.tasks_url = f"{base_url}/tasks/"
    
    def print_response(self, response):
        """Красиво выводит ответ сервера"""
        if response.status_code in [200, 201]:
            data = response.json()
            if data.get("success"):
                print("\n✅ УСПЕХ!")
                print(f"📊 Статус код: {response.status_code}")
                
                if "message" in data:
                    print(f"💬 Сообщение: {data['message']}")
                
                if "data" in data:
                    if isinstance(data["data"], list):
                        print(f"\n📋 Найдено задач: {data.get('count', len(data['data']))}")
                        for i, task in enumerate(data["data"], 1):
                            print(f"\n{'━' * 50}")
                            print(f"   📝 Задача #{i}")
                            print(f"   ID: {task.get('id')}")
                            print(f"   Название: {task.get('title')}")
                            print(f"   Статус: {self.get_status_emoji(task.get('status'))} {task.get('status')}")
                            if task.get('description'):
                                print(f"   Описание: {task.get('description')}")
                            print(f"   Создана: {task.get('created_at')}")
                    else:
                        print("\n📄 Информация о задаче:")
                        task = data["data"]
                        print(f"   ID: {task.get('id')}")
                        print(f"   Название: {task.get('title')}")
                        print(f"   Статус: {self.get_status_emoji(task.get('status'))} {task.get('status')}")
                        if task.get('description'):
                            print(f"   Описание: {task.get('description')}")
                        print(f"   Создана: {task.get('created_at')}")
                        print(f"   Обновлена: {task.get('updated_at')}")
            else:
                print(f"\n❌ ОШИБКА: {data.get('error', 'Неизвестная ошибка')}")
        else:
            print(f"\n❌ ОШИБКА сервера: {response.status_code}")
            try:
                print(f"   Ответ: {response.json()}")
            except:
                print(f"   Текст: {response.text}")
    
    def get_status_emoji(self, status):
        """Возвращает эмодзи для статуса"""
        emojis = {
            "todo": "⏳",
            "in_progress": "⚡",
            "done": "✅"
        }
        return emojis.get(status, "❓")
    
    def get_all_tasks(self):
        """Получить все задачи"""
        print("\n📥 Получаем список задач...")
        try:
            response = requests.get(self.tasks_url)
            self.print_response(response)
        except requests.ConnectionError:
            print("❌ Не удалось подключиться к серверу!")
            print(f"   Проверьте, запущен ли сервер по адресу: {self.base_url}")
    
    def get_task(self, task_id):
        """Получить задачу по ID"""
        print(f"\n🔍 Ищем задачу #{task_id}...")
        try:
            response = requests.get(f"{self.tasks_url}{task_id}/")
            self.print_response(response)
        except requests.ConnectionError:
            print("❌ Не удалось подключиться к серверу!")
    
    def create_task(self, title, description="", status="todo"):
        """Создать новую задачу"""
        print(f"\n📝 Создаем задачу: {title}")
        task_data = {
            "title": title,
            "description": description,
            "status": status
        }
        try:
            response = requests.post(self.tasks_url, json=task_data)
            self.print_response(response)
        except requests.ConnectionError:
            print("❌ Не удалось подключиться к серверу!")
    
    def update_task(self, task_id, title=None, description=None, status=None):
        """Обновить задачу"""
        print(f"\n✏️  Обновляем задачу #{task_id}...")
        
        # Собираем только переданные данные
        update_data = {}
        if title is not None:
            update_data["title"] = title
        if description is not None:
            update_data["description"] = description
        if status is not None:
            update_data["status"] = status
        
        try:
            # Используем PATCH для частичного обновления
            response = requests.patch(f"{self.tasks_url}{task_id}/", json=update_data)
            self.print_response(response)
        except requests.ConnectionError:
            print("❌ Не удалось подключиться к серверу!")
    
    def delete_task(self, task_id):
        """Удалить задачу"""
        print(f"\n🗑️  Удаляем задачу #{task_id}...")
        try:
            response = requests.delete(f"{self.tasks_url}{task_id}/")
            self.print_response(response)
        except requests.ConnectionError:
            print("❌ Не удалось подключиться к серверу!")
    
    def create_sample_tasks(self):
        """Создать тестовые задачи"""
        print("\n🎯 Создаем тестовые задачи...")
        sample_tasks = [
            {"title": "Купить молоко", "description": "3.2% жирности", "status": "todo"},
            {"title": "Сделать домашнее задание", "description": "По операционным системам", "status": "in_progress"},
            {"title": "Запустить Django сервер", "description": "Проверить работу API", "status": "done"},
            {"title": "Изучить Python", "status": "in_progress"},
            {"title": "Сходить в магазин", "status": "todo"}
        ]
        
        for task in sample_tasks:
            self.create_task(**task)

def print_menu():
    """Показать меню"""
    print("\n" + "="*60)
    print("📋 To-Do API КЛИЕНТ")
    print("="*60)
    print("1. 📥  Получить все задачи")
    print("2. 🔍  Получить задачу по ID")
    print("3. 📝  Создать новую задачу")
    print("4. ✏️   Обновить задачу")
    print("5. 🗑️   Удалить задачу")
    print("6. 🎯  Создать тестовые задачи (5 шт)")
    print("7. 🌐  Изменить адрес сервера")
    print("0. 🚪  Выход")
    print("="*60)

def main():
    """Основная функция"""
    print("🚀 Запуск To-Do API клиента...")
    
    # Проверяем подключение к интернету и установку requests
    try:
        import requests
    except ImportError:
        print("\n❌ Библиотека 'requests' не установлена!")
        print("Установите её командой:")
        print("pip install requests")
        return
    
    client = TodoClient()
    
    while True:
        print_menu()
        
        try:
            choice = input("\n👉 Выберите действие (0-7): ").strip()
            
            if choice == "0":
                print("\n👋 До свидания!")
                break
            
            elif choice == "1":
                client.get_all_tasks()
            
            elif choice == "2":
                try:
                    task_id = int(input("Введите ID задачи: "))
                    client.get_task(task_id)
                except ValueError:
                    print("❌ Ошибка: Введите числовой ID")
            
            elif choice == "3":
                title = input("Введите название задачи: ").strip()
                if not title:
                    print("❌ Ошибка: Название не может быть пустым")
                    continue
                
                description = input("Введите описание (необязательно): ").strip()
                status = input("Введите статус (todo/in_progress/done) [по умолчанию todo]: ").strip()
                
                if not status:
                    status = "todo"
                elif status not in ["todo", "in_progress", "done"]:
                    print("❌ Ошибка: Недопустимый статус. Используйте: todo, in_progress или done")
                    continue
                
                client.create_task(title, description, status)
            
            elif choice == "4":
                try:
                    task_id = int(input("Введите ID задачи для обновления: "))
                    
                    print("\n🔄 Что будем обновлять? (оставьте пустым, если не меняется)")
                    title = input("Новое название: ").strip()
                    description = input("Новое описание: ").strip()
                    status = input("Новый статус (todo/in_progress/done): ").strip()
                    
                    # Проверка статуса
                    if status and status not in ["todo", "in_progress", "done"]:
                        print("❌ Ошибка: Недопустимый статус")
                        continue
                    
                    # Преобразуем пустые строки в None
                    title = title if title else None
                    description = description if description else None
                    status = status if status else None
                    
                    client.update_task(task_id, title, description, status)
                except ValueError:
                    print("❌ Ошибка: Введите числовой ID")
            
            elif choice == "5":
                try:
                    task_id = int(input("Введите ID задачи для удаления: "))
                    confirm = input(f"❓ Вы уверены, что хотите удалить задачу #{task_id}? (y/N): ")
                    if confirm.lower() == "y":
                        client.delete_task(task_id)
                    else:
                        print("❌ Удаление отменено")
                except ValueError:
                    print("❌ Ошибка: Введите числовой ID")
            
            elif choice == "6":
                confirm = input("❓ Создать 5 тестовых задач? (y/N): ")
                if confirm.lower() == "y":
                    client.create_sample_tasks()
                else:
                    print("❌ Создание отменено")
            
            elif choice == "7":
                new_url = input("Введите новый адрес сервера [http://localhost:8000/api]: ").strip()
                if new_url:
                    if not new_url.startswith("http"):
                        new_url = "http://" + new_url
                    client = TodoClient(new_url)
                    print(f"✅ Адрес сервера изменен на: {new_url}")
                else:
                    client = TodoClient()
                    print("✅ Адрес сервера сброшен на стандартный")
            
            else:
                print("❌ Ошибка: Выберите вариант от 0 до 7")
            
            input("\n⏎ Нажмите Enter для продолжения...")
        
        except KeyboardInterrupt:
            print("\n\n👋 Выход по Ctrl+C")
            break
        except Exception as e:
            print(f"\n❌ Неожиданная ошибка: {e}")

if __name__ == "__main__":
    main()