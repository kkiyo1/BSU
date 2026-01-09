from django.db import models

class Task(models.Model):
    class StatusChoices(models.TextChoices):
        TODO = 'todo', 'К выполнению'
        IN_PROGRESS = 'in_progress', 'В процессе'
        DONE = 'done', 'Выполнено'
    
    title = models.CharField(
        max_length=200,
        verbose_name='Название задачи'
    )
    
    description = models.TextField(
        verbose_name='Описание задачи',
        blank=True,
        null=True
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
    
    def __str__(self):
        return f"{self.id}: {self.title} ({self.get_status_display()})"