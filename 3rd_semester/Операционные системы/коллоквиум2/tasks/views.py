from rest_framework import views, status
from rest_framework.response import Response
from rest_framework.exceptions import NotFound
from django.db import transaction
from .models import Task
from .serializers import TaskSerializer, TaskListSerializer

class BaseAPIView:
    """Базовый класс для API представлений"""
    
    @staticmethod
    def get_task(pk):
        """Получение задачи по ID"""
        try:
            return Task.objects.get(pk=pk)
        except Task.DoesNotExist:
            raise NotFound(detail=f"Задача с ID {pk} не найдена")

class TaskListView(BaseAPIView, views.APIView):
    """API представление для работы со списком задач"""
    
    def get(self, request):
        """Получение списка всех задач"""
        try:
            tasks = Task.objects.all()
            serializer = TaskListSerializer(tasks, many=True)
            return Response({
                "success": True,
                "data": serializer.data,
                "count": tasks.count()
            }, status=status.HTTP_200_OK)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
    
    @transaction.atomic
    def post(self, request):
        """Создание новой задачи"""
        try:
            serializer = TaskSerializer(data=request.data)
            if serializer.is_valid():
                task = serializer.save()
                return Response({
                    "success": True,
                    "data": TaskSerializer(task).data,
                    "message": "Задача успешно создана"
                }, status=status.HTTP_201_CREATED)
            return Response({
                "success": False,
                "errors": serializer.errors
            }, status=status.HTTP_400_BAD_REQUEST)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class TaskDetailView(BaseAPIView, views.APIView):
    """API представление для работы с конкретной задачей"""
    
    def get(self, request, pk):
        """Получение задачи по ID"""
        try:
            task = self.get_task(pk)
            serializer = TaskSerializer(task)
            return Response({
                "success": True,
                "data": serializer.data
            }, status=status.HTTP_200_OK)
        except NotFound as e:
            return Response({
                "success": False,
                "error": str(e.detail)
            }, status=status.HTTP_404_NOT_FOUND)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
    
    @transaction.atomic
    def put(self, request, pk):
        """Полное обновление задачи"""
        try:
            task = self.get_task(pk)
            serializer = TaskSerializer(task, data=request.data)
            if serializer.is_valid():
                updated_task = serializer.save()
                return Response({
                    "success": True,
                    "data": TaskSerializer(updated_task).data,
                    "message": "Задача успешно обновлена"
                }, status=status.HTTP_200_OK)
            return Response({
                "success": False,
                "errors": serializer.errors
            }, status=status.HTTP_400_BAD_REQUEST)
        except NotFound as e:
            return Response({
                "success": False,
                "error": str(e.detail)
            }, status=status.HTTP_404_NOT_FOUND)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
    
    @transaction.atomic
    def patch(self, request, pk):
        """Частичное обновление задачи"""
        try:
            task = self.get_task(pk)
            serializer = TaskSerializer(task, data=request.data, partial=True)
            if serializer.is_valid():
                updated_task = serializer.save()
                return Response({
                    "success": True,
                    "data": TaskSerializer(updated_task).data,
                    "message": "Задача успешно обновлена"
                }, status=status.HTTP_200_OK)
            return Response({
                "success": False,
                "errors": serializer.errors
            }, status=status.HTTP_400_BAD_REQUEST)
        except NotFound as e:
            return Response({
                "success": False,
                "error": str(e.detail)
            }, status=status.HTTP_404_NOT_FOUND)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
    
    @transaction.atomic
    def delete(self, request, pk):
        """Удаление задачи"""
        try:
            task = self.get_task(pk)
            task.delete()
            return Response({
                "success": True,
                "message": f"Задача с ID {pk} успешно удалена"
            }, status=status.HTTP_200_OK)
        except NotFound as e:
            return Response({
                "success": False,
                "error": str(e.detail)
            }, status=status.HTTP_404_NOT_FOUND)
        except Exception as e:
            return Response({
                "success": False,
                "error": str(e)
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)