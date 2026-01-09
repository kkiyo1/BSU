from rest_framework import views, status
from rest_framework.response import Response
from .models import Task
from .serializers import TaskSerializer

class TaskListView(views.APIView):
    def get(self, request):
        """Получить список всех задач"""
        tasks = Task.objects.all()
        serializer = TaskSerializer(tasks, many=True)
        return Response({
            "success": True,
            "data": serializer.data,
            "count": tasks.count()
        })
    
    def post(self, request):
        """Создать новую задачу"""
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

class TaskDetailView(views.APIView):
    def get_object(self, pk):
        try:
            return Task.objects.get(pk=pk)
        except Task.DoesNotExist:
            return None
    
    def get(self, request, pk):
        """Получить задачу по ID"""
        task = self.get_object(pk)
        if task is None:
            return Response({
                "success": False,
                "error": f"Задача с ID {pk} не найдена"
            }, status=status.HTTP_404_NOT_FOUND)
        
        serializer = TaskSerializer(task)
        return Response({
            "success": True,
            "data": serializer.data
        })
    
    def put(self, request, pk):
        """Полностью обновить задачу"""
        task = self.get_object(pk)
        if task is None:
            return Response({
                "success": False,
                "error": f"Задача с ID {pk} не найдена"
            }, status=status.HTTP_404_NOT_FOUND)
        
        serializer = TaskSerializer(task, data=request.data)
        if serializer.is_valid():
            updated_task = serializer.save()
            return Response({
                "success": True,
                "data": TaskSerializer(updated_task).data,
                "message": "Задача успешно обновлена"
            })
        return Response({
            "success": False,
            "errors": serializer.errors
        }, status=status.HTTP_400_BAD_REQUEST)
    
    def patch(self, request, pk):
        """Частично обновить задачу"""
        task = self.get_object(pk)
        if task is None:
            return Response({
                "success": False,
                "error": f"Задача с ID {pk} не найдена"
            }, status=status.HTTP_404_NOT_FOUND)
        
        serializer = TaskSerializer(task, data=request.data, partial=True)
        if serializer.is_valid():
            updated_task = serializer.save()
            return Response({
                "success": True,
                "data": TaskSerializer(updated_task).data,
                "message": "Задача успешно обновлена"
            })
        return Response({
            "success": False,
            "errors": serializer.errors
        }, status=status.HTTP_400_BAD_REQUEST)
    
    def delete(self, request, pk):
        """Удалить задачу"""
        task = self.get_object(pk)
        if task is None:
            return Response({
                "success": False,
                "error": f"Задача с ID {pk} не найдена"
            }, status=status.HTTP_404_NOT_FOUND)
        
        task.delete()
        return Response({
            "success": True,
            "message": f"Задача с ID {pk} успешно удалена"
        })