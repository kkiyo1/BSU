from rest_framework import serializers
from .models import Task

class TaskSerializer(serializers.ModelSerializer):
    """Сериализатор для модели Task"""
    
    class Meta:
        model = Task
        fields = ['id', 'title', 'description', 'status', 'created_at', 'updated_at']
        read_only_fields = ['id', 'created_at', 'updated_at']
    
    def validate_status(self, value):
        """Валидация статуса"""
        valid_statuses = [choice[0] for choice in Task.StatusChoices.choices]
        if value not in valid_statuses:
            raise serializers.ValidationError(
                f"Недопустимый статус. Допустимые значения: {', '.join(valid_statuses)}"
            )
        return value
    
    def validate_title(self, value):
        """Валидация названия"""
        if not value.strip():
            raise serializers.ValidationError("Название задачи не может быть пустым")
        if len(value) > 200:
            raise serializers.ValidationError("Название задачи не должно превышать 200 символов")
        return value.strip()

class TaskListSerializer(serializers.ModelSerializer):
    """Упрощенный сериализатор для списка задач"""
    class Meta:
        model = Task
        fields = ['id', 'title', 'status', 'created_at']