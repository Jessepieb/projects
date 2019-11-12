import datetime

import sqlalchemy as sa
import sqlalchemy.orm as orm
from data.modelbase import SqlAlchemyBase


class Appointment(SqlAlchemyBase):
    __tablename__ = 'appointments'

    id = sa.Column(sa.Integer, primary_key=True, autoincrement=True)
    title = sa.Column(sa.String, nullable=True)
    created_date = sa.Column(sa.DateTime, default=datetime.datetime.now(), index=True)
    desc = sa.Column(sa.String, nullable=True)

    user_id = sa.Column(sa.Integer, sa.ForeignKey("users.id"))
    user = orm.relation('User')

    def __repr__(self):
        return f'<Appointment {self.id}>'
