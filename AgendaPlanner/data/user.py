import datetime
from typing import List

import sqlalchemy as sa
import sqlalchemy.orm as orm

from data.appointment import Appointment
from data.modelbase import SqlAlchemyBase


class User(SqlAlchemyBase):
    __tablename__ = 'users'

    id = sa.Column(sa.Integer, primary_key=True, autoincrement=True)
    name = sa.Column(sa.String, nullable=True)
    email = sa.Column(sa.String, index=True, unique=True, nullable=True)
    hashed_password = sa.Column(sa.String, nullable=True)
    created_date = sa.Column(sa.DateTime, default=datetime.datetime.now, index=True)
    profile_image_url = sa.Column(sa.String, nullable=True)
    last_login = sa.Column(sa.DateTime, default=datetime.datetime.now, index=True)

    appointments: List[Appointment] = orm.relation('Appointment', order_by=[
        Appointment.id.desc(),
        Appointment.created_date.desc(),
        Appointment.title.desc(),
    ], back_populates='user')
