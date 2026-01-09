from django.db import models
from django.core.exceptions import ValidationError

class Task(models.Model):
    """Модель задачи"""
    
    class StatusChoices(models.TextChoices):
        TODO = 'todo', 'To Do'
        IN_PROGRESS = 'in_progress', 'In Progress'
        DONE = 'done', 'Done'
    
    title = models.CharField(
        max_length=200,
        verbose_name='Название задачи',
        help_text='Введите название задачи'
    )
    
    description = models.TextField(
        verbose_name='Описание задачи',
        blank=True,
        null=True,
        help_text='Подробное описание задачи'
    )
    
    status = models.CharField(
        max_length=20,
        choices=StatusChoices.choices,
        default=StatusChoices.TODO,
        verbose_name='Статус задачи'
    )
    
    created_at = models.DateTimeField(
        auto_now_add=True,
        verbose_name='Дата создания'
    )
    
    updated_at = models.DateTimeField(
        auto_now=True,
        verbose_name='Дата обновления'
    )
    
    class Meta:
        verbose_name = 'Задача'
        verbose_name_plural = 'Задачи'
        ordering = ['-created_at']
    
    def __str__(self):
        return f"{self.id}: {self.title} ({self.get_status_display()})"
    
    def clean(self):
        """Валидация модели"""
        if not self.title.strip():
            raise ValidationError("Название задачи не может быть пустым")
        
        if self.status not in dict(self.StatusChoices.choices):
            raise ValidationError(f"Недопустимый статус. Доступные: {', '.join(self.StatusChoices.values)}")
    
    def save(self, *args, **kwargs):
        """Переопределение save с валидацией"""
        self.full_clean()
        super().save(*args, **kwargs)